#ifndef __USER_HPP__
#define __USER_HPP__

class User
{
public:
	User(std::string name);

	std::string toString() const;

private:
	std::string name;
};

#endif