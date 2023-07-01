#include "common.hpp"
#include "Environment.hpp"
#include "PrintingHelpers.hpp"

const char *Environment::GetEnvironmentName()
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

const char *Environment::GetOppositeEnvironmentName(std::string &currentEnv)
{
    return currentEnv == "tiramisu" ? "aroma" : "tiramisu";
    // if currentEnv is tiramisu, return aroma, else if it is aroma or is legacy, return tiramisu
}

bool Environment::CheckFolderExist(const std::string &path)
{
    if (access(path.c_str(), F_OK) == 0) {
        return true;
    }

    return false;
}

bool Environment::CheckEnvironmentExist(const std::string &environmentName)
{
    if (CheckFolderExist(DEFAULT_ENVIRONMENT_SD_PATH + environmentName))
        return true;
    PrintingHelpers::OS_Print("The environment you are trying to switch to doesn't exist!");
    return false;
}