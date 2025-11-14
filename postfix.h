//  token is a strutcture that facilates parsing a string containing an infix mathematical expression 

typedef struct token token;
struct token {
    double value;
    char opr;
    unsigned precedence;
    bool function;
    char parentheses;
    bool terminator;
};

//  tokenize the string and store the tokens in order in a tokens array

void tok(char *string, token token[]);


//  pushes a token into the end of an array

void push(token stack[],token token);

//  pops the last tokken of a tokken array into another tokken array

void pop(token src[], token dest[]);

//  returns the last tokken of a tokken array

token lastElement(token src[]);

//  Converts a mathematical expression(string) from infix to postfix such that the final expression is represenred with an array tokkens

void postfix(char* string, token output[]);