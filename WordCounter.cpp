#include <string>
#include <fstream>
#include <boost\algorithm\string\classification.hpp>
#include <boost\algorithm\string\split.hpp>
#include "WordCounter.h"
#include "WordCounterException.h"

#define BUFFER_SZ 1024*10
using namespace NTL;

WordCounter::WordCounter(void) {
}

WordCounter::~WordCounter(void) {
}

//	countWords method returns the number of apearing the 'value' in the given file
ZZ WordCounter::countWords(const std::string & filename, const std::string & value) {
	std::ifstream in(filename);
	if(!in.is_open()) {
		throw WordCounterException("\nCould not open the file:\n\n" + filename);
	}
	// check
	std::vector<std::string> words_amount;
	std::vector<std::string>::iterator it;
	std::string tail = "";
	int rnum = 0;
	ZZ counter;
	counter = 0L;
	char buffer [BUFFER_SZ + 1] = { 0 };
	in.read (buffer, BUFFER_SZ);
	if (!in.good() && !in.eof()) {
		throw WordCounterException("\nError with reading. The file:\n\n" + filename);
	}
	buffer[BUFFER_SZ] = '\0';
	rnum = in.gcount();
	while (BUFFER_SZ >= rnum) {
		boost::split(words_amount, buffer, boost::is_any_of(" `~!@#$%^&*()-=_+\|,./<>?\'\"\\\n\t\b"), boost::token_compress_on);
		if (words_amount.empty()) {
			break;
		}
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
		if (!in.good() && !in.eof()) {
			throw WordCounterException("\nError with reading. The file:\n\n" + filename);
		}
		buffer[BUFFER_SZ] = '\0';
		rnum = in.gcount();
	};
	if (!value.compare(tail)) {
		counter++;
	}
	in.close();
	return counter;
}
