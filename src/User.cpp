#include "User.h"

User::User(std::string name, unsigned int id,std::string password) : name(name), id(id),password(password)  {}
User::User(std::vector<std::string> in) {
    this->id = stoi(in[0]);
    this->name = in[1];
    this->password = in[2];
}
User::~User() {}

void User::setName(std::string name) {
    this->name = name;
}

std::string User::getName() const {
    return name;
}

bool User::login(std::string name, std::string password) {
    // Placeholder for actual authentication logic
    if (this->name == name && password == this->password) {
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

std::ostream &operator<<(std::ostream &out, const User &user) {
    out << user.id << " " << user.name << " " << user.password;
    return out;
}