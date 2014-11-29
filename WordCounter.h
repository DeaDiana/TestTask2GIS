#ifndef _WORD_COUNTER_H_
#define _WORD_COUNTER_H_

#include <vector>
#include <string>

class WordCounter
{
public:
	WordCounter(void);
	~WordCounter(void);
	static unsigned long long countWords(const std::string &filename, const std::string &value);
private:
	static std::vector<std::string> split (const std::string & text);
};

#endif /*_WORD_COUNTER_H_*/