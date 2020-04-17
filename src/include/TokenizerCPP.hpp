#pragma once

#include <string>
#include "ITokenizer.hpp"

using namespace TOKEN;

class TokenizerCPP: public ITokenizer
{
public:
    TokenizerCPP();
    TokenizerCPP(std::string symbols, std::vector<std::string> keywords);
    ~TokenizerCPP();
    void SetSource(std::string source) override;
    std::vector<Token> GetTokens() override;
private:
    std::string GetFullString(std::string& fullStr, std::string quoteChar, int& i);
    std::string GetFullRegex(std::string& fullStr, int& i, std::string re);
private:
    std::string m_Source;
    std::string m_Symbols;
    std::vector<std::string> m_Keywords;
};
