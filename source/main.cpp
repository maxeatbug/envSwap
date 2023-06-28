#include "main.hpp"

int main(int argc, char **argv)
{
	std::string environment;
	FILE *defaultcfg;
	FILE *autobootcfg;
	VPADStatus status;
	VPADReadError err;
	bool isAroma = true;
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

	VPADRead(VPAD_CHAN_0, &status, 1, &err);
	
	environment = GetEnvironmentName();
	os_printf("Checking Environment...");

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

	
	os_printf("Modifying file: \'fs:/vol/external01/wiiu/environments/default.cfg\'");
	defaultcfg = fopen("fs:/vol/external01/wiiu/environments/default.cfg","w");
	if (isAroma)
	{
		fputs("tiramisu", defaultcfg);
		os_printf("Wrote \'tiramisu\' to /environments/default.cfg");
	}
	else
	{
		fputs("aroma", defaultcfg);
		os_printf("Wrote \'aroma\' to /environments/default.cfg");
	}
	fclose(defaultcfg);	
	
	if (isAroma)
	{
		os_printf("Modifying file: \'fs:/vol/external01/wiiu/environments/tiramisu/autoboot.cfg\'");
		autobootcfg = fopen("fs:/vol/external01/wiiu/environments/tiramisu/autoboot.cfg", "w");
		if (status.hold & VPAD_BUTTON_B)
		{
			fputs("wiiu_menu", autobootcfg);
			os_printf("Wrote \'wiiu_menu\' to Tiramisu autoboot.");
		}
		else
		{
			fputs("homebrew_launcher", autobootcfg);
			os_printf("Wrote \'homebrew_launcher\' to Tiramisu autoboot.");
		}
		
	}
	else
	{
		os_printf("Modifying file: \'fs:/vol/external01/wiiu/environments/aroma/autoboot.cfg\'");
		autobootcfg = fopen("fs:/vol/external01/wiiu/environments/aroma/autoboot.cfg", "w");
		fputs("wiiu_menu", autobootcfg);
		os_printf("Wrote \'wiiu_menu\' to Aroma autoboot.");
	}

	fclose(autobootcfg);

	finishedSuccessfully = true;
	os_printf("Success!");
exit:
	if (finishedSuccessfully)
		os_printf("Rebooting in 5 seconds...");
	else if (isAroma)
		os_printf("An error occurred! Exiting to menu in 5 seconds...");
	else 
		os_printf("An error occurred! Please press the HOME button to exit...");
	OSScreenFlipBuffers();

	if (isAroma || finishedSuccessfully)
		OSSleepTicks(OSSecondsToTicks(5));

	if (finishedSuccessfully)
		OSLaunchTitle(OS_TITLE_ID_REBOOT, 0);
	else if (isAroma)
	{
		SYSLaunchMenu();
	}

	while (WHBProcIsRunning()) {}
	
	Mocha_DeInitLibrary();

	WHBLogConsoleFree();
	WHBProcShutdown();
	return 0;
}
