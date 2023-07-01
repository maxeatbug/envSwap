#include "common.hpp"

class PrintingHelpers
{
    public:
        static void OSScreenPutFont(uint32_t row, uint32_t column, const char* buffer);
        static void OSScreenClearBuffer(uint32_t color);
        static void OSScreenFlipBuffers();
        static void OS_PrintToScreen(const char* text);
        static void OS_PrintToLog(const char* text);
        static void OS_PrintBlankLine();
        static void OS_Print(const char* text);
};