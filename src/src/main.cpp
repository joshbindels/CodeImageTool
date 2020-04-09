#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <regex>
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




std::string getFullString(std::string& fullStr, std::string quoteChar, int& i)
{
    std::string res = quoteChar;
    i++;
    while(fullStr[i] != quoteChar[0])
    {
        res += fullStr[i++];
    }
    res += fullStr[i++];
    return res;
}

std::string getFullRegex(std::string& fullStr, int& i, std::string re)
{
    std::string res;
    while(std::regex_match(std::string(1, fullStr[i]), std::regex(re)))
    {
        res += fullStr[i++];
    }
    return res;
}

int main(int, char**)
{
    std::vector<Token> lex;

    for(int i=0; i<TEST_STRING.length(); i++)
    {
        std::string symbols = "!%^&*()_+/?.,<>|`~-={}[]";

        if(TEST_STRING[i] == ' ' || TEST_STRING[i] == '\n')
        {
            lex.push_back(Token(TOKEN_TYPE::WHITESPACE, std::string(1, TEST_STRING[i])));
        }
        else if(symbols.find(TEST_STRING[i]) != std::string::npos)
        {
            lex.push_back(Token(TOKEN_TYPE::SYMBOL, std::string(1, TEST_STRING[i])));
        }
        else if(TEST_STRING[i] == '\"' || TEST_STRING[i] == '\'')
        {
            std::string a = getFullString(TEST_STRING, std::string(1, TEST_STRING[i]), i);
            lex.push_back(Token(TOKEN_TYPE::STRING, a));
        }
        else if(std::regex_match(std::string(1, TEST_STRING[i]), std::regex("[.0-9]")))
        {
            std::string a = getFullRegex(TEST_STRING, i, "[.0-9]");
            lex.push_back(Token(TOKEN_TYPE::NUMBER, a));
        }
        else if(std::regex_match(std::string(1, TEST_STRING[i]), std::regex("[_a-zA-Z]")))
        {
            std::string a = getFullRegex(TEST_STRING, i, "[_a-zA-Z]");
            lex.push_back(Token(TOKEN_TYPE::KEYWORD, a));
        }
        else
        {
            lex.push_back(Token(TOKEN_TYPE::UNKNOWN, std::string(1, TEST_STRING[i])));
        }


    }

    for(Token &l: lex)
    {
        LOG(l.ToString());
    }
    return 0;
}
