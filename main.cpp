#include "expression_evaluator/expression_evaluator.hpp"
#include <iostream>
#include <ranges>

int main(int argc, char const *argv[])
{
    auto token_stream = tokenize("A*B+CVASDWEWQ()))()");

    for (auto& x : token_stream)
    {
        std::cout << x.val << std::endl;
    }



    return 0;
}
