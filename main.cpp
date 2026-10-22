#include "expression_evaluator/expression_evaluator.hpp"

#include <iostream>
#include <stdexcept>
#include <utility>
#include <bitset>
#include <cmath>
#include <ranges>
#include <iomanip>

std::string input_expression()
{
    std::string expression;
    std::cout << "Valid Operators: *, +, ~, &, ^, !\n";
    std::cout << "Input boolean expression: ";
    std::getline(std::cin, expression);

    return expression;
}


std::shared_ptr<expr_node> generate_syntax_tree()
{
    while(true)
    {
        try
        {
            auto expression = input_expression();
            auto token_stream = tokenize(expression);
            auto syntax_tree = parse(token_stream);
            return syntax_tree;
        }
        catch(const std::exception& e)
        {
            std::cout << "============================================" << "\n";
            std::cout << "ERROR: " << e.what() << "\n";
            std::cout << "============================================" << "\n";
            continue;
        }
    }
}


void generate_table_values(std::shared_ptr<expr_node> syntax_tree)
{
    int var_count = variables.size();
    int maximum_term_count = std::powl(2, var_count) - 1;


    for (int i = 0; i <= maximum_term_count; i++)
    {
        itl::unordered_map<std::string, bool> variable_mappings;

        int j = 0;
        for (auto&& x : variables | std::views::reverse)
        {
            bool value = (i & (1 << j++)) != 0;
            variable_mappings[x] = value;
        }


        for (auto&& x : variables)
        {
            std::cout << std::setw(5) << variable_mappings[x] << "|  ";
        }
        std::cout <<  std::setw(5) << evaluate(*syntax_tree, variable_mappings) << std::endl;



    }


}


void generate_truth_table(std::shared_ptr<expr_node> syntax_tree)
{

    std::cout << std::endl;
    std::cout << std::endl;


    std::cout << "========================================\n";
    for (auto&& x : variables)
    {
        std::cout << std::left <<std::setw(5) << x << "|  "; 
    }
    std::cout << std::left <<std::setw(20) << "Output: " << std::endl;
    std::cout << "========================================\n";
    generate_table_values(syntax_tree);
}




int main(int argc, char const* argv[])
{
    if (argc > 2)
    {
        std::cout << "ERROR: Too many arguments!!!";
        return 1;
    }

    if (argc == 2)
    {
        try
        {
            std::string hi = argv[1];
            generate_truth_table(parse(tokenize(hi)));
            return 0;
        }
        catch (const std::exception& e)
        {
            std::cout << "ERROR: " << e.what();
            return 1;
        }
    }

    while(true)
    {
        auto hello = generate_syntax_tree();
        generate_truth_table(hello);
        std::cout << std::endl;
        std::cout <<"CTRL + C mon nu dim kayaten (aray ko).\n";
        std::cout << std::endl;
    }
}
