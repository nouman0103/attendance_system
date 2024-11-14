#pragma once
#include <iostream>
#include <string>
class User
{
public:
    User(std::string name, unsigned int id);
    ~User();
    void setName(std::string name);
    std::string getName();
    bool login(unsigned int id, std::string name, std::string password);
    bool logout();
    void setID(unsigned int id);
    unsigned int getID();

private:
    std::string name;
    unsigned int id;
    bool logged_in;
};