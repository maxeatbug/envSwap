#include <coreinit/launch.h>
#include <sysapp/launch.h>
#include <whb/proc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <coreinit/filesystem.h>

// dont question it :)
void OSLaunchTitle(uint64_t titleId, int argc)
{
        OSLaunchTitlel(titleID, argc);
}
