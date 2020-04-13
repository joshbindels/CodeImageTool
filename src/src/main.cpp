#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <regex>
#include "CONST.hpp"

#include <opencv2/opencv.hpp>

#define LOG(x) std::cout << x << std::endl;


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
    Token(TOKEN_TYPE type, std::string value):m_Type(type),m_Value(value){};
    ~Token(){};
    std::string GetValue(){ return m_Value; }
    TOKEN_TYPE GetType(){ return m_Type; }
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
    std::cout << "getFullString" << std::endl;
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
    i--;
    return res;
}

int main(int argc, char** argv)
{
    std::vector<Token> lex;
    std::string TEST_STRING = "int main(int argc, char** argv)\n{\n    int a = 123;\n}";
    std::string symbols = "!%^&*_+/?.,<>|~-=(){}[]";

    std::cout << "String length: " << TEST_STRING.length() << std::endl;
    LOG(TEST_STRING);
    for(int i=0; i<TEST_STRING.length(); i++)
    {
        if(TEST_STRING[i] == ' ')
        {
            lex.push_back(Token(TOKEN_TYPE::WHITESPACE, std::string(1, TEST_STRING[i])));
        }
        else if(TEST_STRING[i] == '\n')
        {
            lex.push_back(Token(TOKEN_TYPE::NEWLINE, std::string(1, TEST_STRING[i])));
        }
        //else if(symbols.find(TEST_STRING[i]) != std::string::npos)
        else if(std::ispunct(TEST_STRING[i]))
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


    cv::Mat image(800, 800, CV_8UC3, cv::Scalar(255, 255, 255));

    int x = 0;
    int y = 20;
    for(Token &l: lex)
    {
        if (l.GetType() == TOKEN_TYPE::NEWLINE)
        {
            y+=20;
            x = 0;
        }
        else
        {
            cv::putText(image, l.GetValue(), cv::Point(x,y), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,0,0));
            x += 10 * l.GetValue().length();
        }
        LOG(l.ToString());
    }

    imwrite("outputimage.jpg", image);

    return 0;
}
