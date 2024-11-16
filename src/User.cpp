#include "User.h"

User::User(std::string name, unsigned int id,std::string password) : name(name), id(id),password(password)  {}
User::User(json j) {
    this->name = j["name"];
    this->id = j["id"];
    this->password = j["password"];
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

json User::to_json() {
    json j;
    j["name"] = name;
    j["id"] = id;
    j["password"] = password;
    return j;
}

std::ostream &operator<<(std::ostream &out, const User &user) {
    out << user.id << " " << user.name << " " << user.password;
    return out;
}