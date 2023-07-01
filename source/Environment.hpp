#include "common.hpp"

class Environment
{
    public:
        static const char *GetEnvironmentName();
        static const char *GetOppositeEnvironmentName(std::string &currentEnv);
        static bool CheckFolderExist(const std::string &path);
        static bool CheckEnvironmentExist(const std::string &environmentName);
};
