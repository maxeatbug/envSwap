#include "main.hpp"

int main(int argc, char **argv)
{
	// wii u boilerplate start
    WHBProcInit();
    WHBLogConsoleInit();
    WHBLogCafeInit();

    if (Mocha_InitLibrary() != MOCHA_RESULT_SUCCESS) {
        os_printf("Mocha_InitLibrary failed");
        return exit();
    }
	// wii u boilerplate end

	return run_boot_change();
}

int exit()
{
	os_printf("An error occurred! Returning to menu in 5 seconds...");
	OSScreenFlipBuffers();
	OSSleepTicks(OSSecondsToTicks(5));
    WHBLogConsoleFree();
    while (WHBProcIsRunning()) {}
    WHBProcShutdown();
    return 0;
}

int run_boot_change()
{
	OSScreenClearBuffer(0);
	
	bool isAroma;
	std::string environment = GetEnvironmentName();

	if (environment.compare("legacy") == 0)
	{
		os_printf("Current Environment is Legacy or Unmodded,");
		os_printf("use Tiramisu/Aroma for this application.");
		return exit();
	}
	else if (environment.compare("aroma") == 0)
	{
		os_printf("Current Environment is Aroma, Swapping to Tiramisu.");
		isAroma = true;
		if (!CheckEnvironmentExist("tiramisu"))
			return exit();
	}
	else if (environment.compare("tiramisu") == 0)
	{
		os_printf("Current Environment is Tiramisu, Swapping to Aroma.");
		isAroma = false;
		if (!CheckEnvironmentExist("aroma"))
			return exit();
	}
	else 
		isAroma = false; // avoid compiler note :P


	FILE *defaultcfg = fopen("fs:/vol/external01/wiiu/environments/default.cfg","w");

	if (isAroma)
		fputs("tiramisu", defaultcfg);
	else
		fputs("aroma", defaultcfg);

	fclose(defaultcfg);	
	

	FILE *autobootcfg;

	if (isAroma)
	{
		autobootcfg = fopen("fs:/vol/external01/wiiu/environments/tiramisu/autoboot.cfg", "w");
		fputs("homebrew_launcher", autobootcfg);
		os_printf("Writing \'homebrew_launcher\' to Tiramisu autoboot.");
	}
	else
	{
		autobootcfg = fopen("fs:/vol/external01/wiiu/environments/aroma/autoboot.cfg", "w");
		fputs("wiiu_menu", autobootcfg);
		os_printf("Writing \'wiiu_menu\' to Aroma autoboot.");
	}

	fclose(autobootcfg);


	os_printf("Rebooting in 5 seconds!");
	OSScreenFlipBuffers();
	OSSleepTicks(OSSecondsToTicks(5));

	OSLaunchTitle(OS_TITLE_ID_REBOOT, 0);
	while (WHBProcIsRunning()) {}
	WHBProcShutdown();
	WHBLogConsoleFree();
	return 0;
}
