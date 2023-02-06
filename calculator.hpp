#include <string>
#include <iostream>
#include <cstdarg>
namespace np_calculator
{
    using std::cerr;
    using std::cin;
    using std::cout;
    using std::endl;
    using std::string;

    bool is_quit(string);
    void error_at(int place, string fmt, ...);

    int calcaulator(void);
    namespace tokenizer
    {
        enum TOKENTYPE
        {
            NUM,
            END,
        };
        class token;
                class token
        {
        private:
            TOKENTYPE type;
            token *next;
            string::const_iterator begin;
            string::const_iterator end;

        public:
            token(const TOKENTYPE type, const string &value) : type(type), begin(value.begin()), end(value.end()){};
            token(){};
            token(const TOKENTYPE type, const string::const_iterator& begin, const string::const_iterator& end): type(type), begin(begin), end(end){};
            void set_next(const TOKENTYPE type, const string::const_iterator& begin, const string::const_iterator& end)
            {
                this->next = new token(type, begin, end);
            }
            token *get_next(void) const
            {
                return this->next;
            }
            TOKENTYPE get_type(void) const
            {
                return this->type;
            }
            string get_string(void) const
            {
                return string(begin, end);
            }
            int get_place(string::const_iterator str_begin) const
            {
                return this->begin - str_begin;
            }
            bool is_type(TOKENTYPE type) const
            {
                return this->type == type;
            }
        };
        void tokenize(const string &expr, bool &err_flag, token* head);
        void go_next_token(token *cur);
        void go_next_word(string::const_iterator &);
        string::const_iterator num(string::const_iterator &);
        bool is_end(string::const_iterator &);
        string::const_iterator num(string::const_iterator &begin)
        {
            go_next_word(begin);
            if (!('0' <= *begin && *begin <= '9'))
            {
                return begin;
            }
            while (*begin == '0')
            {
                ++begin;
            }
            string::const_iterator cur = begin;
            while ('0' <= *cur && *cur <= '9')
            {
                ++cur;
            }
            return cur;
        }
        bool is_end(string::const_iterator &begin)
        {
            go_next_word(begin);
            return *begin == '\n' || *begin == '\0';
        }

        void go_next_word(string::const_iterator &i)
        {
            while (*i == ' ')
            {
                ++i;
            }
        }
        void go_next_token(token *cur)
        {
            token *next = cur->get_next();
            delete cur;
            cur = next;
        }

    }
    namespace new_liner
    {
        void set_attr(string);
        void set_mark(string);
        void new_line(void);
        string new_line_attr;
        string new_line_mark = ">> ";
        void set_attr(string attr)
        {
            new_line_attr = attr;
        };
        void set_mark(string mark)
        {
            new_line_mark = mark;
        };
        void new_line(void)
        {
            cout << new_line_attr << new_line_mark;
        }
    }
    using new_liner::new_line;
    using new_liner::set_attr;
    using new_liner::set_mark;
    using tokenizer::token;
    using tokenizer::tokenize;
    namespace parser
    {
        using tokenizer::go_next_token;
        using tokenizer::TOKENTYPE;

        enum NODETYPE
        {
            NUM,
        };

        class Node;
        Node parse(const token &head);
        class Node
        {
        private:
            NODETYPE type;
            string value;
            Node *lhs;
            Node *rhs;

        public:
            Node() : lhs(nullptr), rhs(nullptr){};
            Node(NODETYPE type) : type(type), lhs(nullptr), rhs(nullptr){};
            Node(NODETYPE type, string value) : type(type), value(value), lhs(nullptr), rhs(nullptr){};
            void connect_l(Node *l) { this->lhs = l; }
            void connect_r(Node *r) { this->rhs = r; }
            void connect(Node *node)
            {
                if (this->lhs)
                {
                    this->lhs = node;
                }
                else
                {
                    this->rhs = node;
                }
            }
            NODETYPE get_type(void) { return this->type; }
            string get_value(void) { return this->value; }
            Node *get_lhs(void) { return this->lhs; }
            Node *get_rhs(void) { return this->rhs; }
        };
    }
    using parser::parse;
}