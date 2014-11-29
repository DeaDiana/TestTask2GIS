#ifndef _PARSING_CMD_LINE_H_
#define _PARSING_CMD_LINE_H_

#include <map>
#include <string>

enum ArgumentsFlags { 
	FILE_FLAG, 
	MODE_FLAG, 
	VALUE_FLAG, 
	HELP_FLAG
};

std::map <ArgumentsFlags, std::string> parseCommandLineIntoTheMapOfParameters(int argc, char * argv[]);
std::string extractOneParameter(const int argc, char * argv[], const int start_position, int * end_position);

#endif /*_PARSING_CMD_LINE_H_*/