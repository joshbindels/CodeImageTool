#include "TokenizerCPP.hpp"

#include <regex>

TokenizerCPP::TokenizerCPP()
    : m_Source("")
    , m_Symbols("[]{}()!@#$%^&*></=-")
    , m_Keywords({"char", "int"})
{

}

TokenizerCPP::TokenizerCPP(std::string symbols, std::vector<std::string> keywords)
    : m_Source("")
    , m_Symbols(symbols)
    , m_Keywords(keywords)
{
}

TokenizerCPP::~TokenizerCPP() {}

void TokenizerCPP::SetSource(std::string source)
{
    m_Source = source;
}

std::vector<Token> TokenizerCPP::GetTokens()
{
    std::vector<Token> res;

    for(int i=0; i<m_Source.length(); i++)
    {
        if(m_Source[i] == ' ')
        {
            res.push_back(Token(TOKEN_TYPE::WHITESPACE, std::string(1, m_Source[i])));
        }
        else if(m_Source[i] == '\n')
        {
            res.push_back(Token(TOKEN_TYPE::NEWLINE, std::string(1, m_Source[i])));
        }
        else if(m_Symbols.find(m_Source[i]) != std::string::npos)
        {
            res.push_back(Token(TOKEN_TYPE::SYMBOL, std::string(1, m_Source[i])));
        }
        else if(m_Source[i] == '\"' || m_Source[i] == '\'')
        {
            std::string a = GetFullString(m_Source, std::string(1, m_Source[i]), i);
            res.push_back(Token(TOKEN_TYPE::STRING, a));
        }
        else if(std::regex_match(std::string(1, m_Source[i]), std::regex("[.0-9]")))
        {
            std::string a = GetFullRegex(m_Source, i, "[.0-9]");
            res.push_back(Token(TOKEN_TYPE::NUMBER, a));
        }
        else if(std::regex_match(std::string(1, m_Source[i]), std::regex("[_a-zA-Z]")))
        {
            std::string fullWord = GetFullRegex(m_Source, i, "[_a-zA-Z]");
            if(std::find(m_Keywords.begin(), m_Keywords.end(), fullWord) != m_Keywords.end())
            {
                res.push_back(Token(TOKEN_TYPE::KEYWORD, fullWord));
            }
            else
            {
                res.push_back(Token(TOKEN_TYPE::UNKNOWN, fullWord));
            }
        }
        else
        {
            res.push_back(Token(TOKEN_TYPE::UNKNOWN, std::string(1, m_Source[i])));
        }

    }

    return res;
}

std::string TokenizerCPP::GetFullString(std::string& fullStr, std::string quoteChar, int& i)
{
    std::string res = quoteChar;
    i++;
    while(fullStr[i] != quoteChar[0])
    {
        res += fullStr[i++];
    }
    res += fullStr[i];
    return res;
}

std::string TokenizerCPP::GetFullRegex(std::string& fullStr, int& i, std::string re)
{
    std::string res;
    while(std::regex_match(std::string(1, fullStr[i]), std::regex(re)))
    {
        res += fullStr[i++];
    }
    i--;
    return res;
}
