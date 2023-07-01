#include "common.hpp"
#include "StringUtils.hpp"

const char *StringUtils::EnsureNullTerminated(const char *str)
{		
    int len = strlen(str);
    if (str[len - 1] != '\0')
    {
        char* tempStr = new char[len];
        strcpy(tempStr, str);
        tempStr[len] = '\0';
        return tempStr;
    }

    return 0;
}

std::string StringUtils::ToString(const char *chars)
{
    std::string newStr = chars;
    return newStr;
}

std::string StringUtils::FirstToUpper(const std::string &str)
{
    if (str.length() == 0)
        return "";

    std::string str2 = std::string(str);

    std::transform(str2.begin(), str2.end(), str2.begin(), ::tolower);
    str2[0] = std::toupper(str2[0]);

    return str2;
}

std::string StringUtils::ToUpper(const std::string &str)
{
    if (str.length() == 0)
        return "";

    std::string str2 = std::string(str);

    std::transform(str2.begin(), str2.end(), str2.begin(), ::toupper);

    return str2;
}