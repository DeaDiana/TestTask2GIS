#ifndef _CHECKER_EXCEPTION_H_
#define _CHECKER_EXCEPTION_H_

#include <exception>

class CheckerException : public std::exception
{
public:
	CheckerException ( const std::string& message ) throw() : errorMessage ( message ) {}
	virtual std::string getMessage() {
		return errorMessage;
	}
	virtual ~CheckerException () throw() {}
private:
	std::string errorMessage;
};

#endif /*_CHECKER_EXCEPTION_H_*/