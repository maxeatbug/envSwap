#include <coreinit/launch.h>
#include <sysapp/launch.h>
#include <whb/proc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <coreinit/filesystem.h>

int main(int argc, char **argv)
{
	FILE *defaultcfg = fopen("fs:/vol/external01/wiiu/environments/default.cfg","w");
		fputs("aroma", defaultcfg);
		fclose(defaultcfg);
	FILE *autobootcfg = fopen("fs:/vol/external01/wiiu/environments/aromam/autoboot.cfg", "w");
		fputs("wiiu_menu", autobootcfg);
		fclose(arfautobootcfg);

	OSLaunchTitlel(OS_TITLE_ID_REBOOT, 0);
	while (WHBProcIsRunning()) {}
	WHBProcShutdown();
	return 0;
}
