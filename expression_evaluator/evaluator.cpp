#include "expression_evaluator.hpp"

bool evaluate(expr_node& node, itl::unordered_map<std::string, bool>& var_mappings)
{

    switch (node.type)
    {
        case node_type::VAR:
            if (node.value == "1")
            {
                return 1;
            }
            else if (node.value == "0")
            {
                return 0;
            }

            return var_mappings[node.value];
            break;

        case node_type::NOT:
            return !evaluate(*node.left, var_mappings);
            break;

        case node_type::AND:
            return evaluate(*node.left, var_mappings) && evaluate(*node.right, var_mappings);
            break;

        case node_type::OR:
            return evaluate(*node.left, var_mappings) || evaluate(*node.right, var_mappings);
            break;

        default:
            throw std::runtime_error("Evaluation Error!!! Incomplete Variable Mappings!");
            break;
    }
}
