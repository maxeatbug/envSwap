#include "main.h"

int main(int argc, char **argv)
{
        bool isAroma = true;
        char* environment = GetEnvironmentName();
        if (strcmp(environment, "tiramisu") == 0) // if environment is tiramisu, you arent on aroma xD
              isAroma = false;

	FILE *defaultcfg = fopen("fs:/vol/external01/wiiu/environments/default.cfg","w");
        if (isAroma) // if on aroma set default to tiramisu
          fputs("tiramisu", defaultcfg);
        else // if on tiramisu set default to aroma
          fputs("aroma", defaultcfg);

        fclose(defaultcfg);

        FILE *autobootcfg;
        if (isAroma) // if on aroma set tiramisu to homebrew_launcher
        {
	  autobootcfg = fopen("fs:/vol/external01/wiiu/environments/tiramisu/autoboot.cfg", "w");
          fputs("homebrew_launcher", autobootcfg);
        }
        else // if on tiramisu set aroma to wiiu_menu
        {
          autobootcfg = fopen("fs:/vol/external01/wiiu/environments/aroma/autoboot.cfg", "w");
          fputs("wiiu_menu", defaultcfg);
        }

        fclose(autobootcfg);

	OSLaunchTitle(OS_TITLE_ID_REBOOT, 0);
	while (WHBProcIsRunning()) {}
	WHBProcShutdown();
	return 0;
}
