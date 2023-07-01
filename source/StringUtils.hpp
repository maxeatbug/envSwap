#include "common.hpp"

class StringUtils
{
    public:
        template <typename... Args>
        static std::string Format(std::string_view rt_fmt_str, Args&&... args) {
            return std::vformat(rt_fmt_str, std::make_format_args(args...));
        }

        static std::string ToString(const char *chars);
        static std::string FirstToUpper(const std::string &str);
        static std::string ToUpper(const std::string &str);
        static const char *EnsureNullTerminated(const char *str);
};
