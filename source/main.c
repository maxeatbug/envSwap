#include "main.h"

int main(int argc, char **argv)
{
	FILE *defaultcfg = fopen("fs:/vol/external01/wiiu/environments/default.cfg","w");
		fputs("aroma", defaultcfg);
		fclose(defaultcfg);
	FILE *autobootcfg = fopen("fs:/vol/external01/wiiu/environments/aroma/autoboot.cfg", "w");
		fputs("wiiu_menu", autobootcfg);
		fclose(autobootcfg);

	OSLaunchTitle(OS_TITLE_ID_REBOOT, 0);
	while (WHBProcIsRunning()) {}
	WHBProcShutdown();
	return 0;
}
