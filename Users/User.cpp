#include "User.h"
#include "System.h"
#include <iostream>
#include <print>
#include <stdexcept>

unsigned int User::countOfUsers = 0;

std::ostream& User::serializeBase(std::ostream& os) const
{
    os << id << " " << username << " " << password << " ";
    return os;
}

User::User(const std::string& username, const std::string& password):username(username), password(password), id(++countOfUsers)
{
   
}

void User::setId(unsigned int newId)
{
    id = newId;
}

const std::string& User::getUsername() const
{
    return username;
}

const std::string& User::getPassword() const
{
    return password;
}

unsigned int User::getId() const
{
    return id;
}

void User::logout(System& system)
{
    system.setCurrentUser(nullptr);
    std::println("Logout is successful.");
}

bool User::changePassword(const std::string& oldPassword, const std::string& newPassword)
{
    if (password != oldPassword) {
        std::println("Wrong password!");
        return false;
    }

    password = newPassword;

    std::println("Password is changed successfully!");

    return true;
}

void User::setCountOfUsers(unsigned int count)
{
    countOfUsers = count;
}


std::ostream& operator<<(std::ostream& os, const User& user)
{
    user.serialize(os);
    return os;
}


