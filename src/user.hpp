#ifndef __USER_HPP__
#define __USER_HPP__

#include <string>

class User
{
public:
	User(std::string name);

	bool compareName(std::string username);

	std::string toString() const;
	
private:
	std::string name;
};

#endif