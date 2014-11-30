#include <string>
#include <fstream>
#include <classification.hpp>
#include <split.hpp>
#include "WordCounter.h"
#include "WordCounterException.h"

#define BUFFER_SZ 1024*10



WordCounter::WordCounter(void) {
}

WordCounter::~WordCounter(void) {
}

//	countWords method returns the number of apearing the 'value' in the given file
unsigned long long WordCounter::countWords(const std::string & filename, const std::string & value) {
	std::ifstream in(filename);
	// check
	std::vector<std::string> words_amount;
	std::vector<std::string>::iterator it;
	std::string tail = "";
	int rnum = 0;
	unsigned long long counter = 0;
	char buffer [BUFFER_SZ + 1] = { 0 };
	in.read (buffer, BUFFER_SZ);
	buffer[BUFFER_SZ] = '\0';
	rnum = in.gcount();
	while (BUFFER_SZ >= rnum) {
		boost::split(words_amount, buffer, boost::is_any_of(" `~!@#$%^&*()-=_+\|,./<>?\'\"\\\n\t\b"), boost::token_compress_on);
		if (words_amount.empty()) {
			break;
		}
		/*if (1 == words_amount.size()) {
			tail += words_amount.front();
			memset(buffer, 0, sizeof(char) * (BUFFER_SZ + 1));
			words_amount.clear();
			if (BUFFER_SZ > rnum) {
				break;
			}
			in.read (buffer, BUFFER_SZ);
			buffer[BUFFER_SZ] = '\0';
			rnum = in.gcount();
			continue;
		}*/
		words_amount[0] = tail.append(words_amount.front());
		tail = words_amount.back();
		words_amount.pop_back();
		it = words_amount.begin();
		for ( ; it != words_amount.end(); it++) {
			if (!value.compare(*it)) {
				counter++;
			}
		}
		memset(buffer, 0, sizeof(char) * (BUFFER_SZ + 1));
		words_amount.clear();
		if (BUFFER_SZ > rnum) {
			break;
		}
		in.read (buffer, BUFFER_SZ);
		buffer[BUFFER_SZ] = '\0';
		rnum = in.gcount();
	};
	if (!value.compare(tail)) {
		counter++;
		std::cout << counter << std::endl;
	}
	return counter;
}
