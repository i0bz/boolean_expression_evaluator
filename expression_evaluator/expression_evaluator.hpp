#pragma once
#include <string>
import iobz_containers;

enum class token_type
{
    VAR,
    NOT,
    AND,
    OR,
    L_PARENTHESIS,
    R_PARENTHESIS,
    END_OF_EXPR
};

struct token
{
    token_type type;
    std::string val;
};

itl::list<token> tokenize(const std::string& expression);

void bracket_matcher(const itl::list<token> tokenize);
