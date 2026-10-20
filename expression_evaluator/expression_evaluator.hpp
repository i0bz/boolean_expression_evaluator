#pragma once

import iobz_containers;

#include <memory>
#include <string>

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

struct token_t
{
    token_type type;
    std::string val;
};

enum class node_type
{
    VAR,
    NOT,
    AND,
    OR
};

struct expr_node
{
    node_type type;
    std::string value;
    std::shared_ptr<expr_node> left;
    std::shared_ptr<expr_node> right;

    expr_node(
        node_type type,
        std::string value = "",
        std::shared_ptr<expr_node> left = nullptr,
        std::shared_ptr<expr_node> right = nullptr) : type(type), value(std::move(value)), left(std::move(left)), right(std::move(right))
    {}
};

bool evaluate(expr_node& node, itl::unordered_map<std::string, bool>& var_mappings);
itl::list<token_t> tokenize(const std::string& expression);
std::shared_ptr<expr_node> parse(itl::list<token_t> token_stream);


