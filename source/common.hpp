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
#include <iostream>
#include <cctype>
#include <algorithm>
#include <format>

#define SD_PATH									"fs:/vol/external01/"
#define DEFAULT_ENVIRONMENT_PATH				"wiiu/environments/"
#define DEFAULT_ENVIRONMENT_SD_PATH				SD_PATH DEFAULT_ENVIRONMENT_PATH
#define DEFAULT_AROMA_ENVIRONMENT_PATH			"wiiu/environments/aroma"
#define DEFAULT_AROMA_ENVIRONMENT_SD_PATH		SD_PATH DEFAULT_AROMA_ENVIRONMENT_PATH
#define DEFAULT_TIRAMISU_ENVIRONMENT_PATH		"wiiu/environments/tiramisu"
#define DEFAULT_TIRAMISU_ENVIRONMENT_SD_PATH	SD_PATH DEFAULT_TIRAMISU_ENVIRONMENT_PATH
#define MAX_SCREEN_LINE_LENGTH					60