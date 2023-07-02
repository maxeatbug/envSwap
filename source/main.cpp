#include "common.hpp"
#include "StringUtils.hpp"
#include "Environment.hpp"
#include "PrintingHelpers.hpp"

int main(int argc, char **argv)
{
	std::string environment;
	std::string oppositeEnvironment;
	FILE *defaultcfg;
	FILE *autobootcfg;
	VPADStatus status;
	VPADReadError err;
	const char *autobootName;
	bool isAroma = false;
	bool finishedSuccessfully = false;

	// wii u boilerplate start
	WHBProcInit();
	WHBLogConsoleInit();
	WHBLogCafeInit();

	if (Mocha_InitLibrary() != MOCHA_RESULT_SUCCESS) {
		PrintingHelpers::OS_Print("Mocha_InitLibrary failed");
		goto exit;
	}
	// wii u boilerplate end

	PrintingHelpers::OSScreenClearBuffer(0);
	PrintingHelpers::OS_PrintBlankLine();

	VPADRead(VPAD_CHAN_0, &status, 1, &err);
	
	environment = Environment::GetEnvironmentName();
	oppositeEnvironment = Environment::GetOppositeEnvironmentName(environment);
	PrintingHelpers::OS_PrintToLog("Checking environment...");
	PrintingHelpers::OS_PrintBlankLine();

	// environment checking
	if (environment.compare("legacy") == 0) // string.compare("string2") == 0 basically just returns true if they are the same
	{
		// extra whitespace in string for proper wrapping
		PrintingHelpers::OS_Print(StringUtils::Format("The current environment is legacy or unmodded, please use   {} and {} for this application.",
			StringUtils::FirstToUpper(oppositeEnvironment),
			StringUtils::FirstToUpper(StringUtils::ToString(Environment::GetOppositeEnvironmentName(oppositeEnvironment)))).c_str()); // get the opposite of the opposite, fallback of opposite is tiramisu, opposite of tiramisu is aroma, so you get tiramisu and aroma
		goto exit;
	}
	else if (environment.compare("aroma") == 0)
		isAroma = true;

	// testing code
	//PrintingHelpers::OS_Print("This is an error exiting test.");
	//goto exit;

	if (!Environment::CheckEnvironmentExist(oppositeEnvironment))
		goto exit;

	PrintingHelpers::OS_Print(StringUtils::Format("The current environment is {}, swapping to {}.",
		StringUtils::ToUpper(environment),
		StringUtils::ToUpper(oppositeEnvironment)).c_str());

	PrintingHelpers::OS_PrintBlankLine();

	// default environment configuration
	PrintingHelpers::OS_PrintToLog(StringUtils::Format("Modifying file: \'{}default.cfg\'", DEFAULT_ENVIRONMENT_SD_PATH).c_str());
	defaultcfg = fopen(StringUtils::Format("{}default.cfg", DEFAULT_ENVIRONMENT_SD_PATH).c_str(), "w");

	if (isAroma)
		fputs("tiramisu", defaultcfg);
	else
		fputs("aroma", defaultcfg);

	PrintingHelpers::OS_Print(StringUtils::Format("Changed default environment to {}.", StringUtils::ToUpper(environment)).c_str());
	fclose(defaultcfg);	
	
	// autoboot configuration
	PrintingHelpers::OS_PrintToLog(StringUtils::Format("Modifying file: \'{}{}/autoboot.cfg\'", DEFAULT_ENVIRONMENT_SD_PATH, oppositeEnvironment).c_str());
	autobootcfg = fopen(StringUtils::Format("{}{}/autoboot.cfg", DEFAULT_ENVIRONMENT_SD_PATH, oppositeEnvironment).c_str(), "w");

	if (isAroma)
	{
		if (status.hold & VPAD_BUTTON_B)
			autobootName = "wiiu_menu";
		else
			autobootName = "homebrew_launcher";
	}
	else
		autobootName = "wiiu_menu";

	fputs(autobootName, autobootcfg);

	PrintingHelpers::OS_Print(StringUtils::Format("{} autoboot set to \'{}\'.", StringUtils::FirstToUpper(oppositeEnvironment), autobootName).c_str());
	PrintingHelpers::OS_PrintBlankLine();

	fclose(autobootcfg);

	// finish up
	finishedSuccessfully = true;
	PrintingHelpers::OS_Print("Environment swap SUCCESS!");
exit:
	// write status to screen, flip buffers, and sleep for 5 seconds
	PrintingHelpers::OS_PrintBlankLine();
	if (finishedSuccessfully)
		PrintingHelpers::OS_Print("Rebooting in 5 seconds...");
	else
		PrintingHelpers::OS_Print("An error occurred! Exiting in 5 seconds...");

	PrintingHelpers::OSScreenFlipBuffers();
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
