#pragma once

#include <vector>
#include "Token.hpp"

class ITokenizer
{
public:
    virtual ~ITokenizer() {};
    virtual void SetSource(std::string source) = 0;
    virtual std::vector<TOKEN::Token> GetTokens() = 0;
};
