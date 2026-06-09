#pragma once
#include <string>
#include "UserValidator.h"
#include <iostream>

class System;

class User
{
private:

	static unsigned int countOfUsers;
	
	unsigned int id;
	std::string username;
	std::string password;

protected:

	std::ostream& serializeBase(std::ostream& os) const;

public:

	User() = default;
	User(const std::string& username, const std::string& password);

	void setId(unsigned int newId);
	static void setCountOfUsers(unsigned int count);

	const std::string& getUsername()const;
	const std::string& getPassword()const;
	unsigned int getId() const;

	void logout(System& system);
	bool changePassword(const std::string& oldPassword, const std::string& newPassword);

	virtual void profileInfo()const = 0;

	virtual std::istream& deserialize(std::istream& is) = 0;
	virtual std::ostream& serialize(std::ostream& os) const = 0;

	virtual ~User() = default;

	friend std::ostream& operator<<(std::ostream& os, const User& user);
	
};

