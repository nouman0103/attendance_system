#include "User.h"

User::User(std::string name, unsigned int id) : name(name), id(id), logged_in(false) {}

User::~User() {}

void User::setName(std::string name) {
    this->name = name;
}

std::string User::getName() {
    return name;
}

bool User::login(unsigned int id, std::string name, std::string password) {
    // Placeholder for actual authentication logic
    if (this->id == id && this->name == name && password == "password") {
        logged_in = true;
        return true;
    }
    return false;
}

bool User::logout() {
    if (logged_in) {
        logged_in = false;
        return true;
    }
    return false;
}

void User::setID(unsigned int id) {
    this->id = id;
}

unsigned int User::getID() {
    return id;
}