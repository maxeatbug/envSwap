#include "main.hpp"

int main(int argc, char **argv)
{
	bool isAroma;
	std::string environment;
	FILE *defaultcfg;
	FILE *autobootcfg;
	bool finishedSuccessfully = false;

	// wii u boilerplate start
    WHBProcInit();
    WHBLogConsoleInit();
    WHBLogCafeInit();

    if (Mocha_InitLibrary() != MOCHA_RESULT_SUCCESS) {
        os_printf("Mocha_InitLibrary failed");
        goto exit;
    }
	// wii u boilerplate end

	OSScreenClearBuffer(0);
	
	environment = GetEnvironmentName();

	if (environment.compare("legacy") == 0)
	{
		os_printf("Current Environment is Legacy or Unmodded,");
		os_printf("use Tiramisu/Aroma for this application.");
		goto exit;
	}
	else if (environment.compare("aroma") == 0)
	{
		os_printf("Current Environment is Aroma, Swapping to Tiramisu.");
		isAroma = true;
		if (!CheckEnvironmentExist("tiramisu"))
			goto exit;
	}
	else if (environment.compare("tiramisu") == 0)
	{
		os_printf("Current Environment is Tiramisu, Swapping to Aroma.");
		isAroma = false;
		if (!CheckEnvironmentExist("aroma"))
			goto exit;
	}
	else 
		isAroma = false; // avoid compiler note :P


	defaultcfg = fopen("fs:/vol/external01/wiiu/environments/default.cfg","w");

	if (isAroma)
		fputs("tiramisu", defaultcfg);
	else
		fputs("aroma", defaultcfg);

	fclose(defaultcfg);	
	
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

	finishedSuccessfully = true;
exit:
	if (finishedSuccessfully)
		os_printf("Rebooting in 5 seconds!");
	else
		os_printf("An error occurred! Exiting in 5 seconds...");
	OSScreenFlipBuffers();

	OSSleepTicks(OSSecondsToTicks(5));

	if (finishedSuccessfully)
		OSLaunchTitle(OS_TITLE_ID_REBOOT, 0);
	else
	{
		SYSLaunchMenu();
	}

	while (WHBProcIsRunning()) {}
	
	Mocha_DeInitLibrary();

	WHBLogConsoleFree();
	WHBProcShutdown();
    return 0;
}
