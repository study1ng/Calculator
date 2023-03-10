#include "calculate.hpp"
#include "command.hpp"

namespace np_calculator
{
    using parser::parse;
}
namespace np_calculator
{
    tokenizer::Token *cur = nullptr;
    parser::Node *head = nullptr;
    int line_number = 0;
    int calculator(void)
    {
        while (true)
        {
            err_flag = false;
            ++line_number;
            set_attr("exp");
            newline();
            string expression;
            getline(cin, expression);
            command::check_command(expression);
            if (command_flag)
            {
                command::Command i = command::tokenize(expression);
                if (err_flag)
                {
                    continue;
                }
                command::do_command(i);
            }
            if (quit_flag)
            {
                return 0;
            }
            if (command_flag || err_flag)
            {
                continue;
            }
            cur = new tokenizer::Token();
            tokenizer::tokenize(expression, *cur);
            if (err_flag)
            {
                continue;
            }
            head = new parser::Node();
            parse(*cur, expression, *head);
            delete cur;
            cur = nullptr;
            if (err_flag)
            {
                continue;
            }
            int ans = calculate::calculate(*head);
            delete head;
            head = nullptr;
            if (err_flag)
            {
                continue;
            }
            use_newline_customized_font();
            set_attr("ans");
            newline();
            cout << ans << endl;
        }
    }
}
int main(void)
{
    try
    {
        np_calculator::calculator();
        np_calculator::set_default();
        np_calculator::use_default_font();
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        np_calculator::set_default();
        np_calculator::use_default_font();
        return 1;
    }
}
