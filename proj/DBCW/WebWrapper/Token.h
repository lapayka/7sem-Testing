#pragma once

#include "facade.h"

class Token
{
private:
    std::string login;
    Role role;
public:
    Token() = default;

    const std::string & getLogin() const { return login; }
    Role getRole() const { return role; }

    ~Token() = default;
};
