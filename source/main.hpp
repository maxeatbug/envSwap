#include <coreinit/launch.h>
#include <coreinit/screen.h>
#include <coreinit/thread.h>
#include <mocha/mocha.h>
#include <string>
#include <whb/log.h>
#include <whb/log_cafe.h>
#include <whb/log_console.h>
#include <whb/proc.h>

int run_boot_change();
int exit();

int lineNumber = 0;
int gClient = -1;

#define OSScreenPutFont(row, column, buffer) ({ \
    OSScreenPutFontEx(SCREEN_TV, row, column, buffer); \
    OSScreenPutFontEx(SCREEN_DRC, row, column, buffer); \
})

#define OSScreenClearBuffer(color) ({ \
    OSScreenClearBufferEx(SCREEN_TV, color); \
    OSScreenClearBufferEx(SCREEN_DRC, color); \
})

#define OSScreenFlipBuffers() ({ \
    OSScreenFlipBuffersEx(SCREEN_TV); \
    OSScreenFlipBuffersEx(SCREEN_DRC); \
})

#define os_printf(text) ({ \
    OSScreenPutFont(0, lineNumber, text); \
    lineNumber++; \
})

#define SD_PATH                                "fs:/vol/external01/"
#define DEFAULT_ENVIRONMENT_PATH               "wiiu/environments/"
#define DEFAULT_ENVIRONMENT_SD_PATH            SD_PATH DEFAULT_ENVIRONMENT_PATH
#define DEFAULT_AROMA_ENVIRONMENT_PATH         "wiiu/environments/aroma"
#define DEFAULT_AROMA_ENVIRONMENT_SD_PATH      SD_PATH DEFAULT_AROMA_ENVIRONMENT_PATH
#define DEFAULT_TIRAMISU_ENVIRONMENT_PATH      "wiiu/environments/tiramisu"
#define DEFAULT_TIRAMISU_ENVIRONMENT_SD_PATH   SD_PATH DEFAULT_TIRAMISU_ENVIRONMENT_PATH

// dont question it :)
void OSLaunchTitle(uint64_t titleId, int argc)
{
    OSLaunchTitlel(titleId, argc);
}

std::string GetEnvironmentName()
{
    char environmentPathBuffer[0x100];
    MochaUtilsStatus status;
    if ((status = Mocha_GetEnvironmentPath(environmentPathBuffer, sizeof(environmentPathBuffer))) != MOCHA_RESULT_SUCCESS)
        return "legacy";

    std::string envPathString(environmentPathBuffer);
  
    if (envPathString.compare(DEFAULT_AROMA_ENVIRONMENT_SD_PATH) == 0)
        return "aroma";
    else if (envPathString.compare(DEFAULT_TIRAMISU_ENVIRONMENT_SD_PATH) == 0)
        return "tiramisu";
    else
        return "legacy";
}

std::string FixPathForFSA(std::string path)
{
    std::string prefix = "fs:/vol";
    std::string replacement = "/vol";

    if (path.substr(0, prefix.size()) == prefix) {
        path.replace(0, prefix.size(), replacement);
    }
    
    return path;
}

bool CheckFolderExist(std::string path) {
    FSADirectoryHandle handle = -1;
    path = FixPathForFSA(path);
    char* pathChars = new char[path.size() + 1];
    std::copy(path.begin(), path.end(), pathChars);
    if (FSAOpenDir(gClient, pathChars, &handle) != FS_ERROR_OK) {
        return false;
    }

    FSACloseDir(gClient, handle);
    return true;
}

bool CheckEnvironmentExist(std::string environmentName)
{
    if (CheckFolderExist(DEFAULT_ENVIRONMENT_SD_PATH + environmentName))
        return true;
    return false;
}