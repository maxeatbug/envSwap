#include <coreinit/launch.h>
#include <sysapp/launch.h>
#include <whb/proc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <coreinit/filesystem.h>
#include <mocha/mocha.h>

#define SD_PATH                                "fs:/vol/external01/"
#define DEFAULT_AROMA_ENVIRONMENT_PATH         "wiiu/environments/aroma"
#define DEFAULT_AROMA_ENVIRONMENT_SD_PATH      SD_PATH DEFAULT_AROMA_ENVIRONMENT_PATH
#define DEFAULT_TIRAMISU_ENVIRONMENT_PATH      "wiiu/environments/tiramisu"
#define DEFAULT_TIRAMISU_ENVIRONMENT_SD_PATH   SD_PATH DEFAULT_TIRAMISU_ENVIRONMENT_PATH

// dont question it :)
void OSLaunchTitle(uint64_t titleId, int argc)
{
    OSLaunchTitlel(titleId, argc);
}

char* GetEnvironmentName()
{
    char environmentPathBuffer[0x100];
    MochaUtilsStatus status;
    if ((status = Mocha_GetEnvironmentPath(environmentPathBuffer, sizeof(environmentPathBuffer))) != MOCHA_RESULT_SUCCESS)
        return "";
  
    if (strcmp(DEFAULT_AROMA_ENVIRONMENT_SD_PATH, environmentPathBuffer) == 0)
        return "aroma";
    if (strcmp(DEFAULT_TIRAMISU_ENVIRONMENT_SD_PATH, environmentPathBuffer) == 0)
        return "tiramisu";

    return "";
}
