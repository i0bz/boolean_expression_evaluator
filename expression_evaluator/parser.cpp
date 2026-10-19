#include "expression_evaluator.hpp"

#include <iterator>
#include <stdexcept>
#include <utility>

namespace
{
    std::shared_ptr<expr_node> parse_primary(itl::list<token_t>& token_stream, itl::list<token_t>::iterator& it);


    int binding_power(token_type type)
    {
        switch (type)
        {
            case token_type::NOT:
                return 3;
            case token_type::AND:
                return 2;
            case token_type::OR:
                return 1;
            default:
                return 0;
        }
    }



    std::shared_ptr<expr_node> parse_expression(itl::list<token_t>& token_stream, itl::list<token_t>::iterator& it, int min_binding_power)
    {
        std::shared_ptr<expr_node> lhs;

        if (it == token_stream.end())
        {
            throw std::runtime_error("Syntax Error!!! Unexpected End Of Stream!");
        }

        if (it->type == token_type::NOT)
        {
            const auto op = *it;
            ++it;
            auto rhs = parse_expression(token_stream, it, binding_power(op.type));
            lhs = std::make_shared<expr_node>(node_type::NOT, op.val, rhs);
        }
        else
        {
            lhs = parse_primary(token_stream, it);
        }

        while (it != token_stream.end())
        {
            const auto& token = *it;

            if (token.type == token_type::END_OF_EXPR || token.type == token_type::R_PARENTHESIS)
            {
                break;
            }

            if (token.type != token_type::AND && token.type != token_type::OR)
            {
                break;
            }

            const int left_binding_power = binding_power(token.type);
            if (left_binding_power < min_binding_power)
            {
                break;
            }

            ++it;
            const int right_binding_power = left_binding_power + 1;
            auto rhs = parse_expression(token_stream, it, right_binding_power);

            const node_type kind = (token.type == token_type::AND) ? node_type::AND : node_type::OR;
            lhs = std::make_shared<expr_node>(kind, token.val, lhs, rhs);
        }

        return lhs;
    }

    
    
    std::shared_ptr<expr_node> parse_primary(itl::list<token_t>& token_stream, itl::list<token_t>::iterator& it)
    {

        const auto token = *it;
        ++it;

        switch (token.type)
        {
            case token_type::VAR:
                return std::make_shared<expr_node>(node_type::VAR, token.val);

            case token_type::L_PARENTHESIS:
            {
                auto inner_expression = parse_expression(token_stream, it, 0);
                if (it == token_stream.end() || it->type != token_type::R_PARENTHESIS)
                {
                    throw std::runtime_error("Syntax Error!!! Mismatched Parentheses!");
                }
                ++it;
                return inner_expression;
            }

            default:
                throw std::runtime_error("Syntax Error!!! Unexpected Token!");
        }
    }


}

std::shared_ptr<expr_node> parse(itl::list<token_t> token_stream)
{
    auto it = token_stream.begin();

    if (it->type == token_type::END_OF_EXPR)
    {
        throw std::runtime_error("Syntax Error!!! Empty Expression!!");
    }

    auto root = parse_expression(token_stream, it, 0);

    if (it == token_stream.end() || it->type != token_type::END_OF_EXPR)
    {
        throw std::runtime_error("Syntax Error!!! Invalid Boolean Expression! Bat nakain yung END token!!!!!!!");
    }

    return root;
}
