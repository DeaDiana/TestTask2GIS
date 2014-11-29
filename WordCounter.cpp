#include <string>
#include <fstream>
#include "WordCounter.h"
#include "WordCounterException.h"

WordCounter::WordCounter(void) {
}

WordCounter::~WordCounter(void) {
}

//	countWords method returns the number of apearing the 'value' in the given file
unsigned long long WordCounter::countWords(const std::string & filename, const std::string & value) {
	std::ifstream in(filename);
	std::string word = "";
	unsigned long long counter = 0;
	in >> word;
	while (!in.eof()) {
		if (!value.compare(word)) {
			counter++;
			if (ULLONG_MAX <= counter) {
				throw WordCounterException("In your file more than " + ULLONG_MAX + std::string(" ") + value);
			}
		}
		in >> word;
	};
	return counter;
}
