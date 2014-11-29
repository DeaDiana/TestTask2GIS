#include <iostream>
#include <time.h>
#include "WordCounter.h"
#include "Helper.h"
#include "Checker.h"
#include "WordCounterException.h"
#include "CheñkerException.h"
#include "parsing_cmd_line.h"

#define FLAG_VALUE_WORDS "words"
#define FLAG_VALUE_CHKSUM "checksum"
#define ERROR_MSG_NEPARAMS "There is not enough parameters"
#define ERROR_MSG_COMMON "Something goes wrong, please look through the help. (The flag is -h)"
#define TIMER_MSG "\nElapsed time in ms: "
#define MS_IN_SEC 1000
#define FOR_COUNTER_RESPONSE "\nNumber of word entries:\n"
#define FOR_CHECKER_RESPONSE "\nThe checksum in chars representation:\n"

void showElapsedTime(long start_time);

int main(int argc, char * argv[]) {
	std::map <ArgumentsFlags, std::string> paramters = parseCommandLineIntoTheMapOfParameters(argc, argv);
	std::map <ArgumentsFlags, std::string>::iterator it_sub = paramters.begin();
	long start_time = clock();
	try {
		for( std::map <ArgumentsFlags, std::string>::iterator it = paramters.begin(); 
			 it != paramters.end(); 
			 it++ ) {
			switch (it->first) {
				case FILE_FLAG:
					it_sub = paramters.find(MODE_FLAG);
					if (paramters.end() == it_sub) {
						std::cerr << ERROR_MSG_NEPARAMS << std::endl;
						showElapsedTime(start_time);
						return -1;
					}
					if (FLAG_VALUE_WORDS == it_sub->second) {
						it_sub = paramters.find(VALUE_FLAG);
						if (paramters.end() != it_sub) {
							std::cout << FOR_COUNTER_RESPONSE << WordCounter::countWords(paramters.at(FILE_FLAG), it_sub->second) << std::endl;
							showElapsedTime(start_time);
							return 0;
						} else {
							std::cerr << ERROR_MSG_NEPARAMS << std::endl;
							showElapsedTime(start_time);
							return -1;
						}
					}
					if (FLAG_VALUE_CHKSUM == it_sub->second) {
						std::cout << FOR_CHECKER_RESPONSE << Checker::countCheckSum(paramters.at(FILE_FLAG)) << std::endl;
						showElapsedTime(start_time);
						return 0;
					}
					std::cerr << ERROR_MSG_NEPARAMS << std::endl;
					showElapsedTime(start_time);
					return -1;
				case HELP_FLAG:
					Helper::printHelp();
					showElapsedTime(start_time);
					return 0;
				default:
					break;
			}
		}
	} catch (WordCounterException & e) {
		std::cerr << e.getMessage() <<std::endl;
	} catch (CheckerException & e) {
		std::cerr << e.getMessage() <<std::endl;
	} catch (std::exception & e) {
		std::cerr << ERROR_MSG_COMMON << std::endl << e.what() << std::endl;
	}
	showElapsedTime(start_time);
	return 0;
}

void showElapsedTime(long start_time) {
	std::cout << TIMER_MSG << (clock() - start_time) * MS_IN_SEC / (double) CLOCKS_PER_SEC << std::endl;
}