#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;


class User
{
public:
    User(std::string name, unsigned int id, std::string password);
    User(json j);
    User(const User &user) = default;
    ~User();
    void setName(std::string name);
    std::string getName() const;
    bool login( std::string name, std::string password);
    void setID(unsigned int id);
    unsigned int getID();
    
    json to_json();
    friend std::ostream &operator<<(std::ostream &out, const User &user);

private:
    std::string name;
    unsigned int id;
    std::string password;
    
};