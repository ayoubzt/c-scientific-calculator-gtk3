

                                                    /*IMPORTANT*/

/*THE STRING MUST END WITH AN UNSIGNIFICANT CHARACHTER " default is ~ " FOR THE FUNCTIONS THAT REQUIRE A STRING TO WORK  */

                                                    /*IMPORTANT*/


// this structure facilates the transition from infix to postfix through assigning components to each significant part of the string

typedef struct token token;
struct token {
    double value;           //for a number
    char operator;          //for an operator
    unsigned precedence;    //for an operator
    char function;          //for a function
    char parentheses;       //for parentheses
    char isNumber;          //for a number
};

// this structure combines an array of the previous strutures with an additional component "top" which allows us to determine where the array ends

typedef struct stack stack;
struct stack {
    token array[1000];
    int top;
};

//this prcedure intilizes the top of a stack to -1

void initStack(stack* Stack);

//this procedure pushes a token to the end of an array of a stack structure and assigns it as the new end

void push(stack* Stack, token Tok);

//this procedure takes a token of a Source stack to and pushes it to the end of Destination Stack

void pop(stack* Source, stack* Dest);

//this procedure parses a string into a stack

void tokenise(char* string, stack* tokens);

//this procedure converts a mathematical expression(string) in the infix form to its equivalent postfix form stored in a stack

void postfix(char* infix, stack* postfix);

//this function evaluates a mathematical experssion(string) and returns the result

double Evaluate(char* string);

