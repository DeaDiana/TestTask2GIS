#ifndef _PARSING_CMD_LINE_H_
#define _PARSING_CMD_LINE_H_

#include <map>
#include <string>

#define FLAG_VALUE_WORDS "words"
#define FLAG_VALUE_CHKSUM "checksum"
#define ERROR_MSG_NEPARAMS "There is not enough parameters"
#define ERROR_MSG_COMMON "Something goes wrong, please look through the help. (The flag is -h)"

enum ArgumentsFlags { 
	FILE_FLAG, 
	MODE_FLAG, 
	VALUE_FLAG, 
	HELP_FLAG
};

std::map <ArgumentsFlags, std::string> parseCommandLineIntoTheMapOfParameters(int argc, char * argv[]);
std::string extractOneParameter(const int argc, char * argv[], const int start_position, int * end_position);

#endif /*_PARSING_CMD_LINE_H_*/