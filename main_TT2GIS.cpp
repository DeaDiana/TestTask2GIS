#include <iostream>
#include <iomanip>
#include <fstream>
#include <time.h>
#include "WordCounter.h"
#include "Helper.h"
#include "Checker.h"
#include "WordCounterException.h"
#include "CheñkerException.h"
#include "parsing_cmd_line.h"

#define FLAG_VALUE_WORDS "words"
#define FLAG_VALUE_CHKSUM "checksum"
#define ERROR_MSG_NEPARAMS "\nThere is not enough parameters"
#define ERROR_MSG_COMMON "\nSomething goes wrong, please look through the help. (The flag is -h)"
#define LINE "\n_________________________________________"
#define TIMER_MSG "\nElapsed time: "
#define MS_IN_SEC 1000
#define FOR_COUNTER_RESPONSE "\nNumber of word entries:\n"
#define FOR_CHECKER_RESPONSE "\nChecksum (hex):\n"
#define NFLGS_MSG "\nPlease look at the help (TestTask2GIS.exe -h)."

void showElapsedTime (long start_time);
void showInfo (const std::string & paramter);
void showInfo (const std::string & file, const std::string & word);

int main(int argc, char * argv[]) {
	if (1 == argc) {
		std::cout << NFLGS_MSG << std::endl;
		return 0;
	}
	long start_time = 0;
	try {
		std::map <ArgumentsFlags, std::string> paramters = parseCommandLineIntoTheMapOfParameters(argc, argv);
		if (paramters.empty()) {
			std::cout << NFLGS_MSG << std::endl;
			return 0;
		}
		std::map <ArgumentsFlags, std::string>::iterator it_sub = paramters.begin();
		start_time = clock();
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
							std::cout << LINE << FOR_COUNTER_RESPONSE << WordCounter::countWords(paramters.at(FILE_FLAG), it_sub->second) << std::endl;
							showElapsedTime(start_time);
							showInfo(paramters.at(FILE_FLAG), it_sub->second);
							return 0;
						} else {
							std::cerr << ERROR_MSG_NEPARAMS << std::endl;
							showElapsedTime(start_time);
							return -1;
						}
					}
					if (FLAG_VALUE_CHKSUM == it_sub->second) {
						std::cout << LINE << FOR_CHECKER_RESPONSE << std::hex << Checker::countCheckSum(paramters.at(FILE_FLAG)) << std::endl;
						showElapsedTime(start_time);
						showInfo(paramters.at(FILE_FLAG));
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
	} catch (ParseCmdLineException & e) {
		std::cerr << e.getMessage() <<std::endl;
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

void showElapsedTime (long start_time) {
	std::cout << LINE << TIMER_MSG << (clock() - start_time) * MS_IN_SEC / (double) CLOCKS_PER_SEC << " ms"<< std::endl;
}
void showInfo (const std::string & file) {
	std::cout << "File: "<< file << std::endl;
	std::ifstream in(file);
	if (in) {
		in.seekg (0, in.end);
		int sz = in.tellg();
		std::cout << "File size: " << sz / ( 1024 * 1024 ) << " Mb" << std::endl;
		in.close();
	}
}
void showInfo (const std::string & file, const std::string & word) {
	showInfo (file);
	std::cout << "Word: " << word << std::endl;
}