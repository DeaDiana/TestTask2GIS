#ifndef _WORD_COUNTER_EXCEPTION_H_
#define _WORD_COUNTER_EXCEPTION_H_

#include <exception>

class WordCounterException : public std::exception
{
public:
	WordCounterException ( const std::string& message ) throw() : errorMessage ( message ) {}
	virtual std::string getMessage() {
		return errorMessage;
	}
	virtual ~WordCounterException() throw() {}
private:
	std::string errorMessage;
};

#endif /*_WORD_COUNTER_EXCEPTION_H_*/
