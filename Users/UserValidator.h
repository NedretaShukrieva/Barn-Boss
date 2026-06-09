#pragma once
#include "User.h"
#include <vector>
#include <memory>


class User;

class UserValidator
{
private:
	static constexpr unsigned int MIN_LENGTH = 3;

public:
	UserValidator() = delete;
	static bool isValidUsername(const std::vector<std::unique_ptr<User>>& users, const std::string& newUsername);
	static bool isValidPassword(const std::string& newPassword);
};

