#include <coreinit/launch.h>
#include <coreinit/screen.h>
#include <coreinit/thread.h>
#include <coreinit/time.h>
#include <coreinit/exit.h>
#include <sysapp/launch.h>
#include <vpad/input.h>
#include <mocha/mocha.h>
#include <string>
#include <unistd.h>
#include <whb/log.h>
#include <whb/log_cafe.h>
#include <whb/log_console.h>
#include <whb/proc.h>
#include <cstring>

#define SD_PATH									"fs:/vol/external01/"
#define DEFAULT_ENVIRONMENT_PATH				"wiiu/environments/"
#define DEFAULT_ENVIRONMENT_SD_PATH				SD_PATH DEFAULT_ENVIRONMENT_PATH
#define DEFAULT_AROMA_ENVIRONMENT_PATH			"wiiu/environments/aroma"
#define DEFAULT_AROMA_ENVIRONMENT_SD_PATH		SD_PATH DEFAULT_AROMA_ENVIRONMENT_PATH
#define DEFAULT_TIRAMISU_ENVIRONMENT_PATH		"wiiu/environments/tiramisu"
#define DEFAULT_TIRAMISU_ENVIRONMENT_SD_PATH	SD_PATH DEFAULT_TIRAMISU_ENVIRONMENT_PATH
#define MAX_SCREEN_LINE_LENGTH					60


// DRC/TV Helpers start
void OSScreenPutFont(uint32_t row, uint32_t column, const char* buffer)
{
	OSScreenPutFontEx(SCREEN_TV, row, column, buffer);
	OSScreenPutFontEx(SCREEN_DRC, row, column, buffer);
}

void OSScreenClearBuffer(uint32_t color)
{
	OSScreenClearBufferEx(SCREEN_TV, color);
	OSScreenClearBufferEx(SCREEN_DRC, color);
}

void OSScreenFlipBuffers()
{
	OSScreenFlipBuffersEx(SCREEN_TV);
	OSScreenFlipBuffersEx(SCREEN_DRC);
}
// DRC/TV Helpers end


// Printing functions start
int lineNumber = 0;

char* EnsureNullTerminated(const char* str)
{
	int len = strlen(str);
    if (str[len - 1] != '\0') {
        char* tempStr = new char[len + 1];
        strcpy(tempStr, str);
        tempStr[len] = '\0';
        return tempStr;
    }

	return 0;
}

void OS_PrintToScreen(const char* text)
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
		char* result = EnsureNullTerminated(text);
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

void OS_PrintToLog(const char* text)
{
	// uncomment the next line to print these log lines to screen aswell
	// OS_PrintToScreen(text);

	// will implement logging here later, placeholder for now
}

void OS_PrintBlankLine()
{
	OS_PrintToLog("");
	lineNumber++;
}

void OS_Print(const char* text)
{
	OS_PrintToScreen(text);
	OS_PrintToLog(text);
}
// Printing functions end


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

bool CheckFolderExist(std::string path)
{
	char* pathChars = new char[path.size() + 1];
	std::copy(path.begin(), path.end(), pathChars);
	
	if (access(pathChars, F_OK) == 0) {
		return true;
	}

	return false;
}

bool CheckEnvironmentExist(std::string environmentName)
{
	if (CheckFolderExist(DEFAULT_ENVIRONMENT_SD_PATH + environmentName))
		return true;
	OS_Print("The environment you are trying to switch to doesn't exist!");
	return false;
}