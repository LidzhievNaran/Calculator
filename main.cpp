#include <iostream>

enum tToken
{
    PLUS, MINUS, MUL, DIV, LPAR, RPAR, NUMBER, END, ERROR
};

tToken aktToken;
double TokenNumber;
char *srcPos;
tToken searchToken()

{
    aktToken = ERROR;
    if (*srcPos==0)
    {
        aktToken = END;
    }
    else
    {
        switch (*srcPos)
        {
            case '(': aktToken=LPAR; break;
            case ')': aktToken=RPAR; break;
            case '*': aktToken=MUL; break;
            case '/': aktToken=DIV; break;
            case '+': aktToken=PLUS; break;
            case '-': aktToken=MINUS; break;
        }
        if (*srcPos>='0'&& *srcPos<'9')
        {
            aktToken=NUMBER;
            TokenNumber = 0.0;
        }
        while (*srcPos>='0' && *srcPos<'9')
        {
            TokenNumber *= 10;
            TokenNumber += *srcPos-'0';
            srcPos++;
        }
        if (aktToken != NUMBER)
        {
            srcPos++;
        }
    }
    return aktToken;
}
tToken Error(char *s)

{
    std::cerr << s << std::endl;
    return ERROR;
}

double PlusMinus();
double Brackets()

{
    double Number;
    switch(aktToken)
    {
        case NUMBER:
            searchToken();
            return TokenNumber;
        case MINUS:
            searchToken();
            return -Brackets();
        case LPAR:
            searchToken();
            Number = PlusMinus();
            if (aktToken != RPAR)
            {
                return Error(") expected");
            }
            searchToken();
            return Number;
        case END:
            return 1;
    }
    return Error("primary expected");
}
double MulDiv()

{
    double Number;

    Number = Brackets();
    while (aktToken==MUL || aktToken==DIV)
    {
        if (aktToken==MUL)
        {
            searchToken();
            Number *= Brackets();
        }
        else if (aktToken==DIV)
        {
            searchToken();
            Number /= Brackets();
        }
    }
    return Number;
}
double PlusMinus()

{
    double Number;

    Number = MulDiv();
    while (aktToken==PLUS || aktToken==MINUS)
    {
        if (aktToken==PLUS)
        {
            searchToken();
            Number += MulDiv();
        }
        else if (aktToken==MINUS)
        {
            searchToken();
            Number -= MulDiv();
        }
    }
    return Number;
}
double analysis(char *s)
{
    srcPos = s;
    searchToken();

    return PlusMinus();
}
int main()
{
    char* demo;
    std::cin>> demo;
    double Number = analysis(demo);
    std::cout << Number << std::endl;
    return 0;
}