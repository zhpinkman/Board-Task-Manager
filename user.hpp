#ifndef __USER_HPP__
#define __USER_HPP__

#include <string>

class User
{
public:
	User(std::string name);

	std::string toString() const;

private:
	std::string name;
};

#endif