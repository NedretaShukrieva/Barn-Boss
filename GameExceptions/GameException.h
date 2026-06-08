#pragma once
#include <stdexcept>
#include <string>

class GameException : public std::runtime_error {
public:
    GameException(const std::string& message)
        : std::runtime_error(message) {}
};

class InvalidProductException : public GameException {
public:
    InvalidProductException()
        : GameException("Invalid product!") {
    }
};

class InvalidUsernameException : public GameException {
public:
    InvalidUsernameException()
        : GameException("Username is already taken!") {
    }
};

class InvalidPasswordException : public GameException {
public:
    InvalidPasswordException()
        : GameException("Password must have at least 3 symbols!") {
    }
};

class InvalidUserTypeException : public GameException {
public:
    InvalidUserTypeException()
        : GameException("Invalid user type!") {
    }
};

class InvalidFileFormatException : public GameException {
public:
	InvalidFileFormatException()
		: GameException("Invalid file format!") {

	}
};
