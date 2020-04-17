#pragma once

#include <string>
#include <sstream>

namespace TOKEN
{

enum TOKEN_TYPE
{
    STRING,
    NUMBER,
    SYMBOL,
    WHITESPACE,
    ASSIGNMENT,
    KEYWORD,
    NEWLINE,
    UNKNOWN
};

inline std::string TranslateTokenTypeToString(TOKEN_TYPE& t)
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
        case TOKEN_TYPE::NEWLINE:
            return "NEWLINE";
        case TOKEN_TYPE::UNKNOWN:
            return "UNKNOWN";
        default:
            return "";
    }
}


class Token
{
public:
    Token(TOKEN_TYPE type, std::string value):m_Type(type), m_Value(value){}
    ~Token(){};
    std::string GetValue() { return m_Value; }
    TOKEN_TYPE GetType() { return m_Type; }
    std::string ToString()
    {
        std::ostringstream res;
        res << "(";
        res << TranslateTokenTypeToString(m_Type);
        res << ", ";
        res << m_Value;
        res << ")";
        return res.str();
    }
private:
    TOKEN_TYPE m_Type;
    std::string m_Value;

};

};
