#include <iostream>

#define MAX_CHAR 512

enum OP
{
    MUL,
    DIV,
    ADD,
    SUB,
    EQUAL
};

enum OP_PRECEDENCE
{
    ADD_SUB,
    MUL_DIV
};

int 
StringLength(char* s)
{
    int c = 0;
    
    while(*(s++) != '\0'){ ++c; }
    
    return c;
}

void
CatStrings(char *Source, 
           char *Dest)
{
    while(*(Dest)) ++Dest;
    
    while(*Source) *(Dest++) = *(Source++);
    
    *Dest = '\0';
}

int
ParseInt(const char* s, const char** r)
{
	int Result = 0;
	int Sign = 0;
    
	while (*s == ' ' || *s == '\t')	++s;
    
	Sign = (*s == '-') ? -1 : 1;
	if (Sign < 0) ++s;
    
	while((unsigned(*s - '0') < 10))
	{
		Result = Result * 10.0f + (*s - '0');
		++s;
	}
    
    *r = s;
    
	return Result;
}

int 
ParseOp(const char* s, const char** e)
{
    int Operator = 0;
    switch(*(s++))
    {
        case '*':
        {
            Operator = OP::MUL;
        }break;
        
        case '/':
        {
            Operator = OP::DIV;
        }break;
        
        case '+':
        {
            Operator = OP::ADD;
        }break;
        
        case '-':
        {
            Operator = OP::SUB;
        }break;
        default:
        {
            Operator = OP::EQUAL;
        }break;
    }
    
    *e = s;
    
    return Operator;
}

int GetOpPrecedence(int Op)
{
    switch(Op)
    {
        case OP::MUL:
        {
            return OP_PRECEDENCE::MUL_DIV;
        }break;
        
        case OP::DIV:
        {
            return OP_PRECEDENCE::MUL_DIV;
        }break;
        
        case OP::ADD:
        {
            return OP_PRECEDENCE::ADD_SUB;
        }break;
        
        case OP::SUB:
        {
            return OP_PRECEDENCE::ADD_SUB;
        }break;
        default:
        {
            return 0;
        }break;
    }
}

int CalculateResult(int L, int R, int Op)
{
    int Result = 0;
    switch(Op)
    {
        case OP::MUL:
        {
            Result = L * R;
        }break;
        
        case OP::DIV:
        {
            Result = L / R;
        }break;
        
        case OP::ADD:
        {
            Result = L + R;
        }break;
        
        case OP::SUB:
        {
            Result = L - R;
        }break;
        case OP::EQUAL:
        {
            Result = L = R ;
        }break;
    }
    
    return Result;
}

int CalculateExpressionLoop(const char* s)
{
    int Result = 0;
    int Left = 0;
    int Right = 0;
    int Check = 0;
    int Operator = 0;
    int Precedence = 0;
    
    while(*(s) != '\0')
    {
        Left = Result;
        Check = ParseInt(s, &s);
        
        if(Check)
        {
            Left = Check;
        }
        
        Operator = ParseOp(s, &s);
        Precedence = GetOpPrecedence(Operator);
        Right = ParseInt(s, &s);
        
        Result = CalculateResult(Left, Right, Operator);
    }
    
    return Result;
}

int CalculateExpressionRecursive(const char* s)
{
    int Left = 0;
    int Right = 0;
    int Operator = 0;
    int Precedence = 0;
    int LastPrecedence = 0;
    
    Left = ParseInt(s, &s);
    Operator = ParseOp(s, &s);
    Precedence = GetOpPrecedence(Operator);
    
    LastPrecedence = Precedence;
    
    const char* Check = s;
    
    if(*(Check++) == '\0')
    { 
        Right = Left;
        return Right;
    }
    
    Right = CalculateExpressionRecursive(s);
    
    return CalculateResult(Left, Right, Operator);
}

int 
main(int argc, char **argv)
{
    char* Line = (char*)malloc(MAX_CHAR);
    memset(Line, 0, MAX_CHAR);
    
    for(int i = 1; i < argc; ++i)
    {
        CatStrings(argv[i], Line);
    }
    
    int Result = {};
    int Left = 0;
    int Right = 0;
    int Operator = 0;
    int Check = 0;
    
    const char* LineMem = Line;
    
    Result = CalculateExpressionLoop(LineMem);
    printf("%i\n", Result);
    
    Result = CalculateExpressionRecursive(LineMem);
    printf("%i\n", Result);
    
    return 0;
}
