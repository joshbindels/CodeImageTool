#include "gtest/gtest.h"

#include "TokenizerCPP.hpp"

TEST(THISISTHETEST, THISISATEST)
{
    std::string TEST_STRING = "int main(int argc, char** argv)\n{\n    char* a = \"Hello\";\n}";
    std::string TEST_SYMBOLS = "()*,;={}";
    std::vector<std::string> TEST_KEYWORDS = {"int", "char"};
    std::vector<TOKEN::Token> ExpectedTokens = {
        Token(TOKEN::TOKEN_TYPE::KEYWORD, "int"),
        Token(TOKEN::TOKEN_TYPE::WHITESPACE, " "),
        Token(TOKEN::TOKEN_TYPE::UNKNOWN, "main"),
        Token(TOKEN::TOKEN_TYPE::SYMBOL, "("),
        Token(TOKEN::TOKEN_TYPE::KEYWORD, "int"),
        Token(TOKEN::TOKEN_TYPE::WHITESPACE, " "),
        Token(TOKEN::TOKEN_TYPE::UNKNOWN, "argc"),
        Token(TOKEN::TOKEN_TYPE::SYMBOL, ","),
        Token(TOKEN::TOKEN_TYPE::WHITESPACE, " "),
        Token(TOKEN::TOKEN_TYPE::KEYWORD, "char"),
        Token(TOKEN::TOKEN_TYPE::SYMBOL, "*"),
        Token(TOKEN::TOKEN_TYPE::SYMBOL, "*"),
        Token(TOKEN::TOKEN_TYPE::WHITESPACE, " "),
        Token(TOKEN::TOKEN_TYPE::UNKNOWN, "argv"),
        Token(TOKEN::TOKEN_TYPE::SYMBOL, ")"),
        Token(TOKEN::TOKEN_TYPE::NEWLINE, "\n"),
        Token(TOKEN::TOKEN_TYPE::SYMBOL, "{"),
        Token(TOKEN::TOKEN_TYPE::NEWLINE, "\n"),
        Token(TOKEN::TOKEN_TYPE::WHITESPACE, " "),
        Token(TOKEN::TOKEN_TYPE::WHITESPACE, " "),
        Token(TOKEN::TOKEN_TYPE::WHITESPACE, " "),
        Token(TOKEN::TOKEN_TYPE::WHITESPACE, " "),
        Token(TOKEN::TOKEN_TYPE::KEYWORD, "char"),
        Token(TOKEN::TOKEN_TYPE::SYMBOL, "*"),
        Token(TOKEN::TOKEN_TYPE::WHITESPACE, " "),
        Token(TOKEN::TOKEN_TYPE::UNKNOWN, "a"),
        Token(TOKEN::TOKEN_TYPE::WHITESPACE, " "),
        Token(TOKEN::TOKEN_TYPE::SYMBOL, "="),
        Token(TOKEN::TOKEN_TYPE::WHITESPACE, " "),
        Token(TOKEN::TOKEN_TYPE::STRING, "\"Hello\""),
        Token(TOKEN::TOKEN_TYPE::SYMBOL, ";"),
        Token(TOKEN::TOKEN_TYPE::NEWLINE, "\n"),
        Token(TOKEN::TOKEN_TYPE::SYMBOL, "}"),
    };
    TokenizerCPP p(TEST_SYMBOLS, TEST_KEYWORDS);
    p.SetSource(TEST_STRING);
    std::vector<TOKEN::Token> ResultTokens = p.GetTokens();

    EXPECT_EQ(ResultTokens.size(), ExpectedTokens.size());

    for(int i=0; i<ResultTokens.size(); i++)
    {
        EXPECT_EQ(ResultTokens.at(i).GetType(), ExpectedTokens.at(i).GetType());
        EXPECT_EQ(ResultTokens.at(i).GetValue(), ExpectedTokens.at(i).GetValue());
    }
}
