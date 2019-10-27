#include "user.hpp"

User::User(std::string name) {
	this->name = name;
}

bool User::compareName(std::string name) const {
	return this->name == name;
}

std::string User::toString() const {
	return name;
}