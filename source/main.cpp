#include "main.hpp"

int main(int argc, char **argv)
{
	// wii u boilerplate start
    WHBProcInit();
    WHBLogConsoleInit();
    WHBLogCafeInit();

    if (Mocha_InitLibrary() != MOCHA_RESULT_SUCCESS) {
        WHBLogPrintf("Mocha_InitLibrary failed");
        WHBLogConsoleDraw();
        OSSleepTicks(OSMillisecondsToTicks(3000));
        return exit();
    }


    FSAInit();
    gClient = FSAAddClient(NULL);
    if (gClient == 0) {
        WHBLogPrintf("Failed to add FSAClient");
        WHBLogConsoleDraw();
        OSSleepTicks(OSMillisecondsToTicks(3000));
        return exit();
    }
    if (Mocha_UnlockFSClientEx(gClient) != MOCHA_RESULT_SUCCESS) {
        FSADelClient(gClient);
        WHBLogPrintf("Failed to add FSAClient");
        WHBLogConsoleDraw();
        OSSleepTicks(OSMillisecondsToTicks(3000));
        return exit();
    }

	// wii u boilerplate end

	run_boot_change();
	exit();
}

int exit()
{
    WHBLogConsoleFree();
    WHBProcShutdown();
    return 0;
}

int run_boot_change()
{
	OSScreenClearBuffer(0);
	
	bool isAroma = true;
	std::string environment = GetEnvironmentName();
	if (environment.compare("tiramisu") == 0)
	{
		os_printf("Current Environment is Tiramisu, Swapping to Aroma");
		isAroma = false;
	}
  

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

	os_printf("Rebooting in 5 Seconds!");
	OSScreenFlipBuffers();
	OSSleepTicks(OSSecondsToTicks(5));
	

	OSLaunchTitle(OS_TITLE_ID_REBOOT, 0);
	while (WHBProcIsRunning()) {}
	WHBProcShutdown();
	return 0;
}