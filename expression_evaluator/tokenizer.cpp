#include "expression_evaluator.hpp"

#include <cctype>
#include <stdexcept>
#include <string>

itl::list<token_t> tokenize(const std::string& expression)
{
    itl::list<token_t> token_stream;
    std::string variable_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (char x : expression)
    {
        if (std::isspace(x))
        {
            continue;
        }
        if (variable_chars.find(x) != std::string::npos)
        {
            token_stream.push_back(token_t{token_type::VAR, std::string(1,x)});
            continue;
        }
        switch (x)
        {
            case '~':
            case '!':
                token_stream.push_back(token_t{token_type::NOT, std::string(1,x)});
                break;

            case '&':
            case '^':
            case '*':
                token_stream.push_back(token_t{token_type::AND, std::string(1,x)});
                break;
            
            case '+':
                token_stream.push_back(token_t{token_type::OR, std::string(1,x)});
                break;

            case ')':
                token_stream.push_back(token_t{token_type::R_PARENTHESIS, std::string(1,x)});
                break;

            case '(':
                token_stream.push_back(token_t{token_type::L_PARENTHESIS, std::string(1,x)});
                break;

            default:
                throw std::runtime_error("Syntax Error!!! Unexpected character: ");
                break;
        }
        
    }


    token_stream.push_back(token_t{token_type::END_OF_EXPR, ""});
    return token_stream;
}