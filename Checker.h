#ifndef _CHECKER_H_
#define _CHECKER_H_

#include <string>

class Checker
{
public:
	Checker(void);
	~Checker(void);
	static std::string countCheckSum(const std::string &filename);
};

#endif /*_CHECKER_H_*/