#pragma once
#include <iostream>
#include <vector>
#include <string>
class User
{
public:
    User(std::string name, unsigned int id);
    User(std::vector<std::string> in);
    ~User();
    void setName(std::string name);
    std::string getName() const;
    bool login(unsigned int id, std::string name, std::string password);
    bool logout();
    void setID(unsigned int id);
    unsigned int getID();
    friend std::ostream &operator<<(std::ostream &out, const User &user);

private:
    std::string name;
    unsigned int id;
    bool logged_in;
};