#include "common.hpp"
#include "PrintingHelpers.hpp"
#include "StringUtils.hpp"

// DRC/TV Helpers start
void PrintingHelpers::OSScreenPutFont(uint32_t row, uint32_t column, const char* buffer)
{
	OSScreenPutFontEx(SCREEN_TV, row, column, buffer);
	OSScreenPutFontEx(SCREEN_DRC, row, column, buffer);
}

void PrintingHelpers::OSScreenClearBuffer(uint32_t color)
{
	OSScreenClearBufferEx(SCREEN_TV, color);
	OSScreenClearBufferEx(SCREEN_DRC, color);
}

void PrintingHelpers::OSScreenFlipBuffers()
{
	OSScreenFlipBuffersEx(SCREEN_TV);
	OSScreenFlipBuffersEx(SCREEN_DRC);
}
// DRC/TV Helpers end


// Printing functions start
int lineNumber = 0;

void PrintingHelpers::OS_PrintToScreen(const char* text)
{
	int len = strlen(text);
    
    if (len <= MAX_SCREEN_LINE_LENGTH)
	{
        OSScreenPutFont(0, lineNumber, text);
		lineNumber++;
    } 
	else
	{

		// ensure the result is null terminated, if it isnt (result != 0), set the text to the null terminated result
		const char* result = StringUtils::EnsureNullTerminated(text);
		if (result != 0)
			text = result;
        int numSubstrings = len / MAX_SCREEN_LINE_LENGTH;  // Calculate the number of substrings needed
        
        for (int i = 0; i < numSubstrings + 1; ++i) 
		{
            int startPos = i * MAX_SCREEN_LINE_LENGTH;
            int substrLen = (i == numSubstrings) ? len - startPos : MAX_SCREEN_LINE_LENGTH;  // Last substring may be shorter
            
            char substring[MAX_SCREEN_LINE_LENGTH + 1];
            strncpy(substring, text + startPos, substrLen);
            substring[substrLen] = '\0';
            
            OSScreenPutFont(0, lineNumber, substring);
			lineNumber++;
        }
    }
}

void PrintingHelpers::OS_PrintToLog(const char* text)
{
	// uncomment the next line to print these log lines to screen aswell
	// OS_PrintToScreen(text);

	// will implement logging here later, placeholder for now
}

void PrintingHelpers::OS_PrintBlankLine()
{
	OS_PrintToLog("");
	lineNumber++;
}

void PrintingHelpers::OS_Print(const char* text)
{
	OS_PrintToScreen(text);
	OS_PrintToLog(text);
}
// Printing functions end