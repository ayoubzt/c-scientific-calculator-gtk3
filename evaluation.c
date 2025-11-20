#include <string.h>
#include <stdio.h>
#include <math.h>
#include "evaluation.h"

void initStack(stack* Stack) {
    Stack->top = -1;
}

void initToken(token* tok) {
    *tok = (token){0, 0, 0, 0, 0, 0};
}

void push(stack* Stack, token Tok) {
    Stack->top++;
    Stack->array[Stack->top] = Tok;
} 

void pop(stack* Source, stack* Dest) {
    push(Dest, Source->array[Source->top]);
    Source->top--;
}

void tokenise(char* string, stack* tokens) {
    initStack(tokens);
    token temp; initToken(&temp);
    const token multiply = {0, '*', 2, 0, 0 ,0};
    unsigned i=0;
    double decimal=0; 
    char charachterHolder[2] = "\0";
    while (string[i] != '\0') {
        charachterHolder[0] = string[i];
        if (string[i] == '.') decimal=0.1;
        else if (string[i] >= '0' && string[i] <= '9') {
            temp.isNumber = 1;
            if (decimal == 0) temp.value = temp.value*10 + string[i]-'0';
            else {temp.value += (string[i]-'0')*decimal; decimal*=0.1;}
        } else {
            if(temp.isNumber) {
                push(tokens, temp); initToken(&temp);
                charachterHolder[0] = string[i];
                if(strpbrk(charachterHolder, "(cstlSep")) push(tokens, multiply);
            }
            decimal = 0;
            switch (string[i]) {
                //constants
                case 'e': temp.value = 2.718281; temp.isNumber = 1; push(tokens, temp); initToken(&temp);    break;
                case 'p': temp.value = 3.141592; temp.isNumber = 1; push(tokens, temp); initToken(&temp);    break;

                //parentheses
                case '(': temp.parentheses = '('; push(tokens, temp); initToken(&temp);                  break;
                case ')': temp.parentheses = ')'; push(tokens, temp); initToken(&temp);                  break;

                //operators
                case '+': temp.operator = '+'; temp.precedence = 1; push(tokens, temp); initToken(&temp); break;
                case '-': temp.operator = '-'; temp.precedence = 1; push(tokens, temp); initToken(&temp); break;
                case '*': temp.operator = '*'; temp.precedence = 2; push(tokens, temp); initToken(&temp); break;
                case '/': temp.operator = '/'; temp.precedence = 2; push(tokens, temp); initToken(&temp); break;
                case '^': temp.operator = '^'; temp.precedence = 3; push(tokens, temp); initToken(&temp); break;

                //functions
                case 'c': temp.function = 'c'; push(tokens, temp); initToken(&temp);                      break;
                case 's': temp.function = 's'; push(tokens, temp); initToken(&temp);                      break;
                case 't': temp.function = 't'; push(tokens, temp); initToken(&temp);                      break;
                case 'l': temp.function = 'l'; push(tokens, temp); initToken(&temp);                      break;
                case 'S': temp.function = 'S'; push(tokens, temp); initToken(&temp);                      break;
                case 'f': temp.function = 'f'; push(tokens, temp); initToken(&temp);                      break;
            }
            if ((tokens->array[tokens->top].parentheses == ')' || tokens->array[tokens->top].value == 2.718281 || tokens->array[tokens->top].value == 3.141592) && ((string[i+1] >= '0' && string[i+1] <= '9') || string[i+1] == 'e' || string[i+1] == 'p')) push(tokens, multiply);
        }
        i++;
    }
}

void postfix(char* infix, stack* postfix) {
    stack Stack, Operators;
    initStack(postfix); initStack(&Operators);
    tokenise(infix, &Stack);
    for (int i = 0; i<=Stack.top; i++) {
        if (Stack.array[i].isNumber) push(postfix, Stack.array[i]);
        else if (Stack.array[i].function || Stack.array[i].parentheses == '(') push(&Operators, Stack.array[i]);
        else if (Stack.array[i].parentheses == ')') {
            while(Operators.array[Operators.top].parentheses != '(') {
                pop(&Operators, postfix);
            }
            Operators.top = Operators.top - 1;
            if (Operators.array[Operators.top].function) pop(&Operators, postfix);
        }
        else {
            if (Stack.array[i].precedence > Operators.array[Operators.top].precedence) push(&Operators, Stack.array[i]);
            else {
                while (1) {
                    pop(&Operators, postfix);
                    if (Stack.array[i].precedence > Operators.array[Operators.top].precedence)  {push(&Operators, Stack.array[i]); break;}
                }
            }
        }
    }
    for (int i = Operators.top; i >= 0; i--) {
        pop(&Operators, postfix);
    }
}

double Evaluate(char* string) {
    stack queue, output, Stack;
    initStack(&output); initStack(&Stack);
    postfix(string, &queue);
    for (int i = 0; i <= queue.top; i++) {
        if(queue.array[i].isNumber) {push(&Stack, queue.array[i]);}
        else if (queue.array[i].function) {
            switch (queue.array[i].function) {
                case 'c': Stack.array[Stack.top].value = cos(Stack.array[Stack.top].value); break;
                case 's': Stack.array[Stack.top].value = sin(Stack.array[Stack.top].value); break;
                case 't': Stack.array[Stack.top].value = tan(Stack.array[Stack.top].value); break;
                case 'S': if (Stack.array[Stack.top].value >= 0) {
                                Stack.array[Stack.top].value = sqrt(Stack.array[Stack.top].value); break;
                            } else {return NAN; break;}
                // case 'l': if(Stack.array[Stack.top].value >= 0) {
                //                 Stack.array[Stack.top].value = ln(Stack.array[Stack.top].value); break;
                //             } else {return NAN; break;}
                // case 'f': if(isNatural(Stack.array[Stack.top].value)) {
                //           Stack.array[Stack.top].value = sqrt(Stack.array[Stack.top].value); break;
                //             } else {return NAN; break;}          
                
            }   
        } else {
            switch (queue.array[i].operator) {
                case '+': Stack.array[Stack.top-1].value += Stack.array[Stack.top].value; Stack.top--; break;
                case '-': Stack.array[Stack.top-1].value -= Stack.array[Stack.top].value; Stack.top--; break;
                case '*': Stack.array[Stack.top-1].value *= Stack.array[Stack.top].value; Stack.top--; break;
                case '/': Stack.array[Stack.top-1].value /= Stack.array[Stack.top].value; Stack.top--; break;
                case '^': if (Stack.array[Stack.top-1].value || Stack.array[Stack.top].value) {
                          Stack.array[Stack.top-1].value =  pow(Stack.array[Stack.top-1].value, Stack.array[Stack.top].value); Stack.top--; break;
                          } else {return NAN; break;}
                
            }
        }
    }
    return Stack.array[0].value;
} 