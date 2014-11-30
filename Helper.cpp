#include <iostream>
#include <string>
#include "Helper.h"

#define HELP_TEXT "\n[TestTask2GIS]\n\n\
The program allows count the number of occurrences\n\
the particular word in given file or calculate file's checksum.\n\n\
Next flags are supported:\n\
-f : Points name of file or full path to it.\n\
-m : Mode could be pointed as 'checksum' or 'words'.\n\
	In 'checksum' mode, app returns 32-bits checksum of given file.\n\
	In 'words' mode, app returns how many entries of some word in the file.\n\
-v : Points the sought-for sequence of english letters.\n\n\
Examples:\n\
1. TestTask2GIS.exe -f Test 1.tst -m words -v mother\n\
2. TestTask2GIS.exe -f Test 1.tst -m checksum\n\
3. TestTask2GIS.exe -h\n\
\n\
Thanks for trying out TestTask2GIS.\n\
Diana Anisutina."

Helper::Helper(void) {
}


Helper::~Helper(void) {
}

void Helper::printHelp() {
	std::cout << HELP_TEXT << std::endl;
}