#include <iostream>
#include "WordCounter.h"
#include "Helper.h"
#include "Checker.h"
#include "WordCounterException.h"
#include "CheñkerException.h"
#include "parsing_cmd_line.h"

int main(int argc, char * argv[]) {
	// parse parameters
	std::map <ArgumentsFlags, std::string> paramters = parseCommandLineIntoTheMapOfParameters(argc, argv);
	std::map <ArgumentsFlags, std::string>::iterator it = paramters.begin();
	std::map <ArgumentsFlags, std::string>::iterator it_sub = paramters.begin();
	try {
		for( ; it != paramters.end(); it++) {
			switch (it->first)
			{
				case FILE_FLAG:
					it_sub = paramters.find(MODE_FLAG);
					if (paramters.end() == it_sub) {
						std::cerr << ERROR_MSG_NEPARAMS <<std::endl;
						return -1;
					}
					if (FLAG_VALUE_WORDS == it_sub->second) {
						it_sub = paramters.find(VALUE_FLAG);
						if (paramters.end() != it_sub) {
							WordCounter::countWords(paramters.at(FILE_FLAG), it_sub->second);
						} else {
							std::cerr << ERROR_MSG_NEPARAMS <<std::endl;
							return -1;
						}
					}
					if (FLAG_VALUE_CHKSUM == it_sub->second) {
						std::cout << Checker::countCheckSum(paramters.at(FILE_FLAG)) << std::endl;
					}
					return 0;
				case HELP_FLAG:
					Helper::printHelp();
					return 0;
				default:
					break;
			}
	
		}
	} catch (WordCounterException & e){
	
	} catch (CheckerException & e) {
	
	} catch (std::exception & e) {
		std::cerr << ERROR_MSG_COMMON <<std::endl;
	}
	return 0;
}