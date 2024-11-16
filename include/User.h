#pragma once
#include <iostream>
#include <vector>
#include <string>
class User
{
public:
    User(std::string name, unsigned int id, std::string password);
    User(std::vector<std::string> in);
    ~User();
    void setName(std::string name);
    std::string getName() const;
    bool login( std::string name, std::string password);
    void setID(unsigned int id);
    unsigned int getID();
    friend std::ostream &operator<<(std::ostream &out, const User &user);

private:
    std::string name;
    unsigned int id;
    std::string password;
    
};