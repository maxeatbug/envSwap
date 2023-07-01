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
		OS_Print("Mocha_InitLibrary failed");
		goto exit;
	}
	// wii u boilerplate end

	OSScreenClearBuffer(0);

	VPADRead(VPAD_CHAN_0, &status, 1, &err);
	
	environment = GetEnvironmentName();
	OS_Print("Checking Environment...");
	OS_PrintBlankLine();

	// environment checking
	if (environment.compare("legacy") == 0)
	{
		isAroma = false;
		OS_Print("The current environment is legacy or unmodded, please use   Tiramisu/Aroma for this application."); // whitespace for proper wrapping
		goto exit;
	}
	else if (environment.compare("aroma") == 0)
	{
		isAroma = true;
		OS_Print("The current environment is Aroma, swapping to Tiramisu.");
		if (!CheckEnvironmentExist("tiramisu"))
			goto exit;
	}
	else if (environment.compare("tiramisu") == 0)
	{
		isAroma = false;
		OS_Print("The current environment is Tiramisu, swapping to Aroma.");
		if (!CheckEnvironmentExist("aroma"))
			goto exit;
	}
	OS_PrintBlankLine();

	// default environment configuration
	OS_PrintToLog("Modifying file: \'fs:/vol/external01/wiiu/environments/default.cfg\'");
	defaultcfg = fopen("fs:/vol/external01/wiiu/environments/default.cfg","w");
	if (isAroma)
	{
		fputs("tiramisu", defaultcfg);
		OS_Print("Changed default environment to Tiramisu.");
	}
	else
	{
		fputs("aroma", defaultcfg);
		OS_Print("Changed default enviroment to Aroma.");
	}
	fclose(defaultcfg);	
	
	// autoboot configuration
	if (isAroma)
	{
		OS_PrintToLog("Modifying file: \'fs:/vol/external01/wiiu/environments/tiramisu/autoboot.cfg\'");
		autobootcfg = fopen("fs:/vol/external01/wiiu/environments/tiramisu/autoboot.cfg", "w");
		if (status.hold & VPAD_BUTTON_B)
		{
			fputs("wiiu_menu", autobootcfg);
			OS_Print("Wrote \'wiiu_menu\' to Tiramisu autoboot.");
		}
		else
		{
			fputs("homebrew_launcher", autobootcfg);
			OS_Print("Wrote \'homebrew_launcher\' to Tiramisu autoboot.");
		}
		
	}
	else
	{
		OS_Print("Modifying file: \'fs:/vol/external01/wiiu/environments/aroma/autoboot.cfg\'");
		autobootcfg = fopen("fs:/vol/external01/wiiu/environments/aroma/autoboot.cfg", "w");
		fputs("wiiu_menu", autobootcfg);
		OS_Print("Wrote \'wiiu_menu\' to Aroma autoboot.");
	}
	OS_PrintBlankLine();

	fclose(autobootcfg);

	finishedSuccessfully = true;
	OS_Print("Environment swap successful!");
exit:
	// write status to screen, flip buffers, and sleep for 5 seconds
	OS_PrintBlankLine();
	if (finishedSuccessfully)
		OS_Print("Rebooting in 5 seconds...");
	else
		OS_Print("An error occurred! Exiting to menu in 5 seconds...");

	OSScreenFlipBuffers();
	OSSleepTicks(OSSecondsToTicks(5));

	if (finishedSuccessfully)
		OSLaunchTitlel(OS_TITLE_ID_REBOOT, 0);
	else if (isAroma)
		SYSLaunchMenu();

	while (WHBProcIsRunning())
	{
		if (!isAroma)
			break;
	}
	
	// exit code
	Mocha_DeInitLibrary();

	WHBLogConsoleFree();
	WHBProcShutdown();

	return 0;
}
