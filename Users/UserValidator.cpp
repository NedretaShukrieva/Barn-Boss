#include "UserValidator.h"
#include "User.h"

bool UserValidator::isValidUsername(const std::vector<std::unique_ptr<User>>& users, const std::string& newUsername)
{
    auto it = std::find_if(users.begin(), users.end(), [&newUsername](const std::unique_ptr<User>& user) {
        return user->getUsername() == newUsername;
        });

    return it == users.end();
}

bool UserValidator::isValidPassword(const std::string& newPassword)
{
    return newPassword.length() >= 3;
}
