#include "User.h"

User::User(std::string name, unsigned int id,std::string password) : name(name), id(id),password(password)  {
    // Constructor for User
}
User::User(json j) {
    // Constructor for User from json
    this->name = j["name"];
    this->id = j["id"];
    this->password = j["password"];
}


User::~User() {}

void User::setName(std::string name) {
    // setName: Set the name of the user
    this->name = name;
}

std::string User::getName() const {
    // getName: Get the name of the user
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
    // setID: Set the ID of the user
    this->id = id;
}

unsigned int User::getID() {
    // getID: Get the ID of the user
    return id;
}

json User::to_json() {
    // to_json: Convert the user to json
    json j;
    j["name"] = name;
    j["id"] = id;
    j["password"] = password;
    return j;
}

std::ostream &operator<<(std::ostream &out, const User &user) {
    // operator<<: Overload the << operator for User
    out << user.id << " " << user.name << " " << user.password;
    return out;
}