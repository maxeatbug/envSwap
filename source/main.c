#include "main.h"

int main(int argc, char **argv)
{
        bool isAroma = true;
        char* environment = GetEnvironmentName();
        if (strcmp(environment, "tiramisu") == 0)
              isAroma = false;

	FILE *defaultcfg = fopen("fs:/vol/external01/wiiu/environments/default.cfg","w");
        if (isAroma)
          fputs("aroma", defaultcfg);
        else
          fputs("tiramisu", defaultcfg);

        fclose(defaultcfg);

        FILE *autobootcfg;
        if (isAroma)
        {
	  autobootcfg = fopen("fs:/vol/external01/wiiu/environments/aroma/autoboot.cfg", "w");
          fputs("wiiu_menu", autobootcfg);
        }
        else
        {
          autobootcfg = fopen("fs:/vol/external01/wiiu/environments/tiramisu/autoboot.cfg", "w");
          fputs("homebrew_launcher", defaultcfg);
        }

        fclose(autobootcfg);

	OSLaunchTitle(OS_TITLE_ID_REBOOT, 0);
	while (WHBProcIsRunning()) {}
	WHBProcShutdown();
	return 0;
}
