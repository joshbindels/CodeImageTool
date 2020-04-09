#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "CONST.hpp"

#define LOG(x) std::cout << x << std::endl;


enum TOKEN_TYPE
{
    STRING,
    NUMBER,
    SYMBOL,
    WHITESPACE,
    ASSIGNMENT,
    KEYWORD,
    UNKNOWN
};


std::string TranslateTokenTypeToString(TOKEN_TYPE& t)
{
    switch(t)
    {
        case (TOKEN_TYPE::STRING):
            return "STRING";
        case TOKEN_TYPE::NUMBER:
            return "NUMBER";
        case TOKEN_TYPE::SYMBOL:
            return "SYMBOL";
        case TOKEN_TYPE::WHITESPACE:
            return "WHITESPACE";
        case TOKEN_TYPE::ASSIGNMENT:
            return "ASSIGNMENT";
        case TOKEN_TYPE::KEYWORD:
            return "KEYWORD";
        case TOKEN_TYPE::UNKNOWN:
            return "UNKNOWN";
        default:
            return "";
    }
}

class Token
{
public:
    Token(TOKEN_TYPE type, std::string value):m_Type(type),m_Value(value){};
    ~Token(){};
    std::string ToString()
    {
        std::ostringstream ss;
        ss << "(";
        ss << TranslateTokenTypeToString(m_Type);
        ss << ", ";
        ss << m_Value;
        ss << ")";
        return ss.str();
    }
private:
    TOKEN_TYPE m_Type;
    std::string m_Value;
};




int main(int, char**)
{
    std::vector<Token> lex;

    for(char &c: TEST_STRING)
    {
        TOKEN_TYPE t = TOKEN_TYPE::UNKNOWN;
        std::string value;
        std::string symbols = "!@#$%^&*()_+/?.,<>|\\~`±§-={}[]";

        if(c == ' ' || c == '\n')
        {
            t = TOKEN_TYPE::WHITESPACE;
        }
        else if (symbols.find(c) != std::string::npos)
        {
            t = TOKEN_TYPE::SYMBOL;
        }

        value = c;
        lex.push_back(Token(t, value));
    }

    for(Token &l: lex)
    {
        LOG(l.ToString());
    }
    return 0;
}
