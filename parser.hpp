#pragma once
#include "tokenizer.hpp"
namespace np_calculator
{
    using tokenizer::Token;
    using tokenizer::tokenize;
    namespace parser
    {
        class Node;
        enum NODETYPE
        {
            NUM,
            PLUS,
            MINUS,
            MUL,
            DIV,
            MOD,
        };

        using tokenizer::go_next_token;
        using tokenizer::TOKENTYPE;
        void num(Token &begin, const string &expr, Node &cur);
        void primary(Token &begin, const string &exp, Node &head);
        void mul(Token &begin, const string &exp, Node &head);
        void expr(Token &begin, const string &exp, Node &head);
        int calculate(const Node &begin);
        bool consume(TOKENTYPE type, Token &i);
        void expect(TOKENTYPE type, Token &i, const string &expr);
        void expect(const char *expected, Token &actual, const string &expr);
        int stodigit(const string &i);
        Node parse(const Token &begin, const string &exp);
    }

    namespace parser
    {
        class Node
        {
        private:
            NODETYPE type;
            string::const_iterator begin, end;
            Node *lhs = nullptr;
            Node *rhs = nullptr;

        public:
            Node();
            Node(NODETYPE type);
            Node(NODETYPE type, const string::const_iterator &b, const string::const_iterator &e);
            void connect_l(Node *l);

            void connect_r(Node *r);
            NODETYPE get_type();
            string get_value();
            string::const_iterator get_begin();
            string::const_iterator get_end();
            Node *get_lhs(void);
            Node *get_rhs(void);
        };
    }
}