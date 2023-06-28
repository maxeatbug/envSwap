#include "main.hpp"

int main(int argc, char **argv)
{
	bool isAroma = true;
	std::string environment = GetEnvironmentName();
	if (environment.compare("tiramisu") == 0)
		isAroma = false;
  

	FILE *defaultcfg = fopen("fs:/vol/external01/wiiu/environments/default.cfg","w");

	if (isAroma)
		fputs("tiramisu", defaultcfg);
	else
		fputs("aroma", defaultcfg);

	fclose(defaultcfg);


	FILE *autobootcfg;
	
	if (isAroma = true)
	{
		autobootcfg = fopen("fs:/vol/external01/wiiu/environments/tiramisu/autoboot.cfg", "w");
		fputs("homebrew_launcher", autobootcfg);
	}
	else
	{
		autobootcfg = fopen("fs:/vol/external01/wiiu/environments/aroma/autoboot.cfg", "w");
		fputs("wiiu_menu", autobootcfg);
	}

	fclose(autobootcfg);


	OSLaunchTitle(OS_TITLE_ID_REBOOT, 0);
	while (WHBProcIsRunning()) {}
	WHBProcShutdown();
	return 0;
}
