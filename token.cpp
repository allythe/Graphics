#include "token.h"
#include "logic.h"

#include<string>
#include<fstream>


#include"std_lib_facilities.h"

Token_stream ts;

void Token_stream::putback(Token t)
{
    if (full)
        error("putback() into a full buffer");
    buffer = t;
    full = true;
}

Token Token_stream::get()
{
    if (full)
    {
        full = false;
        return buffer;
    }

    char ch = ' ';
    char ch2 = ' ';

    while (isspace(ch) && ch != print && !iscntrl(ch))
    {

        if (cin)
            cin.get(ch);
        else
            ch = 'q';
    }

    switch (ch)
    {
    case '(':
    case '|':
    case ')':
    case ',':
    case poww:
    case '%':
    case '/':
    case '*':
    case fact:
    case pnc:
    case print:
    case sqrtt:
    case quit:
    case '+':
    case '-':
    case '=':
        return Token{ch};

    case '.':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9': {

        cin.putback(ch);
        double val;
        cin >> val;
        return Token{number, val};
    }

    default:
        if (isalpha(ch))
        {
            string s;
            s += ch;

            while (cin.get(ch) && (isalpha(ch) || isdigit(ch)))
                s += ch;
            cin.putback(ch);

            if (s == power)
                return Token{poww};
            if (s == helpS)
                return Token{help};
            if (s == declkey)
                return Token{let};

            return Token{name, s};
        }
        error(" Bad token ");
        break;
    }
}


void Token_stream::ignore(char c)
{
    if (full && c == buffer.kind)
    {
        full = false;
        return;
    }
    full = false;
    char ch;

    while (cin.get(ch)){
        if (ch=='\0')
            return;
        if (ch == c)
            return ;
    }

    return;
}
