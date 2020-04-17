#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <regex>
#include <algorithm>
#include "CONST.hpp"
#include <opencv2/opencv.hpp>
#include "TokenizerCPP.hpp"

#define LOG(x) std::cout << x << std::endl;


int main(int argc, char** argv)
{
    std::string TEST_STRING = "int main(int argc, char** argv)\n{\n    char* a = \"Hello\";\n}";

    TokenizerCPP tokenizer;
    tokenizer.SetSource(TEST_STRING);
    std::vector<TOKEN::Token> tokens = tokenizer.GetTokens();


    cv::Mat image(800, 800, CV_8UC3, cv::Scalar(255, 255, 255));

    int x = 5;
    int y = 20;
    for(Token &l: tokens)
    {
        if (l.GetType() == TOKEN_TYPE::NEWLINE)
        {
            y+=20;
            x = 5;
        }
        else
        {
            switch(l.GetType())
            {
                case TOKEN_TYPE::KEYWORD:
                    cv::putText(image, l.GetValue(), cv::Point(x,y), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(158,0,148));
                    x += 12 * l.GetValue().length();
                    break;
                case TOKEN_TYPE::STRING:
                    cv::putText(image, l.GetValue(), cv::Point(x,y), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(158,95,0));
                    x += 12 * l.GetValue().length();
                    break;
                case TOKEN_TYPE::WHITESPACE:
                    x += 8;
                        //cv::putText(image, l.GetValue(), cv::Point(x,y), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0,0,0));
                    break;
                default:
                    cv::putText(image, l.GetValue(), cv::Point(x,y), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0,0,0));
                    x += 12 * l.GetValue().length();
                    break;
            }
        }
        LOG(l.ToString());
    }

    imwrite("outputimage.jpg", image);

    return 0;
}
