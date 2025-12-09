#include <string.h>
#include <stdio.h>
#include <math.h>
#include "evaluation.h"
#include "custom_math.h"

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
                if(strpbrk(charachterHolder, "(cstlSepa")) push(tokens, multiply);
            }
            decimal = 0;
            switch (string[i]) {
                //constants
                case 'e': temp.value = 2.718281; temp.isNumber = 1; push(tokens, temp); initToken(&temp);    break;
                case 'p': temp.value = 3.141592; temp.isNumber = 1; push(tokens, temp); initToken(&temp);    break;
                case 'a': temp.value = result;   temp.isNumber = 1; push(tokens, temp); initToken(&temp);    break;

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
                case 'L': temp.function = 'L'; push(tokens, temp); initToken(&temp);                      break;
                case 'S': temp.function = 'S'; push(tokens, temp); initToken(&temp);                      break;
                case 'f': temp.function = 'f'; push(tokens, temp); initToken(&temp);                      break;
                case '_': temp.function = '_'; push(tokens, temp); initToken(&temp);                      break;
            }
            if ((tokens->array[tokens->top].parentheses == ')' || tokens->array[tokens->top].value == 2.718281 || tokens->array[tokens->top].value == 3.141592) && ((string[i+1] >= '0' && string[i+1] <= '9') || string[i+1] == 'e' || string[i+1] == 'p' || string[i+1] == 'a')) push(tokens, multiply);
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
    stack queue;
    postfix(string, &queue);
    for (int i = 0; i <= queue.top; i++) {
        if(queue.array[i].isNumber) {push(&SStack, queue.array[i]);}
        else if (queue.array[i].function) {
            switch (queue.array[i].function) {
                case 'c': if (angle == 'D') SStack.array[SStack.top].value *= (3.141592/180);    
                          SStack.array[SStack.top].value = cosine(SStack.array[SStack.top].value);            break;
                case 's': if (angle == 'D') SStack.array[SStack.top].value *= (3.141592/180);
                          SStack.array[SStack.top].value = sine(SStack.array[SStack.top].value);              break;
                case 't': if (angle == 'D') SStack.array[SStack.top].value *= (3.141592/180);
                          SStack.array[SStack.top].value = tangent(SStack.array[SStack.top].value);           break;
                case 'S': SStack.array[SStack.top].value = square_root(SStack.array[SStack.top].value);       break;
                case 'l': SStack.array[SStack.top].value = log(SStack.array[SStack.top].value);               break;
                case 'L': SStack.array[SStack.top].value = log(SStack.array[SStack.top].value)/log(10);       break;
                case 'f': SStack.array[SStack.top].value = factorial(SStack.array[SStack.top].value);         break;     
                case '_': SStack.array[SStack.top].value *= -1;                                               break;
        
            }   
        } else {
            switch (queue.array[i].operator) {
                case '+': SStack.array[SStack.top-1].value += SStack.array[SStack.top].value; SStack.top--; break;
                case '-': SStack.array[SStack.top-1].value -= SStack.array[SStack.top].value; SStack.top--; break;
                case '*': SStack.array[SStack.top-1].value *= SStack.array[SStack.top].value; SStack.top--; break;
                case '/': SStack.array[SStack.top-1].value /= SStack.array[SStack.top].value; SStack.top--; break;
                case '^': if (SStack.array[SStack.top-1].value || SStack.array[SStack.top].value) {
                          SStack.array[SStack.top-1].value =  pow(SStack.array[SStack.top-1].value, SStack.array[SStack.top].value); SStack.top--; break;
                          } else {return NAN; break;}
                
            }
        }
    }
    return SStack.array[0].value;
} 