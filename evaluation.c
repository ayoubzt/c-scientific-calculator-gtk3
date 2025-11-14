#include <stdbool.h>
#include "evaluation.h"


void tok(char *string, token token[]) {
    unsigned i = 0, e = 0;
    double r = 1;
    for (int i = 0; i<1000; i++) {
    token[i].value = 0;
    token[i].opr = '\0';
    token[i].precedence = 0;
    token[i].function = '\0';
    token[i].parentheses = '\0';
    token[i].terminator = true;
   }
    while(string[i] != '\0') {
        token[e].terminator = false;
        if (string[i] == '.'){
            r = 0.1;
        }else if (string[i] >= 48 && string[i] <= 57) {
            if (r>=1){ 
                token[e].value = token[e].value*10 + (string[i]-48);
            } else {
                token[e].value += (string[i]-48)*r;
                r*= 0.1;
            }
        } else {
            r=1;
            e++;
            token[e].terminator = false;
            switch (string[i]) {
                case 'e':
                    token[e].value = 2.718281;
                    e++;
                    break;
                case 'p':
                    token[e].value = 3.141592;
                    e++;
                    break;
                case '+':
                    token[e].opr = '+';
                    token[e].precedence = 1;
                    break;
                case '-':
                    token[e].opr = '-';
                    token[e].precedence = 1;
                    break;
                case '*':
                    token[e].opr = '*';
                    token[e].precedence = 2;
                    break;
                case '/':
                    token[e].opr = '/';
                    token[e].precedence = 2;
                    break;
                case '^':
                    token[e].opr = '^';
                    token[e].precedence = 3;
                    break;
                case '_':
                    token[e].function = '_';
                    break;
                case '(':
                    token[e].parentheses = '(';
                    break;
                case ')':
                    token[e].parentheses = ')';
                    break;
                
                case 's':
                    token[e].function = 's';
                    break;
                case 'c':
                    token[e].function = 'c';
                    break;
                case 't':
                    token[e].function = 't';
                    break;
                case '!':
                    token[e].function = '!';
                    break;
                case 'S':
                    token[e].function = 'S';
                    break;
                case 'l':
                    token[e].function = 'l';
                    break;
                case 'n':
                    token[e].function = 'n';
                    break;
            }
            if (string[i+1] >= 48 && string[i+1] <= 57) e++;
        }
        i++;

    }
}

void push(token stack[],token token){
    for (unsigned i = 0; i < 1000; i++) {
        if (stack[i].terminator == true) {
            stack[i] = token;
            break;
        }
    }
}
void pop(token src[], token dest[]) {
    int index = -1;
    for (unsigned i = 0; i < 1000; i++) {
        if (index == -1) {
        if (src[i].terminator == true){
            index = i-1;
            if (index == -1) break;
            i = 0;
        }}  else if (dest[i].terminator == true) {
                dest[i] = src[index];
                src[index] = (token){0, '\0', 0, '\0', '\0', true};
                break;
            }
        
    }

}

token lastElement(token src[]) {
    unsigned i =0;
    while (src[i].terminator == false) {
        i++;
    }
    if (i == 0) return src[0];
    else return src[i-1];
}

void postfix(char* string, token output[]) {
    token operatorStack[1000], queue[1000];
    unsigned i = 0, e;
    for (int e = 0; e < 1000; e++) {
        queue[e] = operatorStack[e] = output[e] = (token){0, '\0', 0, '\0', '\0', true};
    }
    tok(string, queue);
    while (queue[i].terminator == false) {
        if(queue[i].opr) {
            repeat:
            if (queue[i].precedence > lastElement(operatorStack).precedence) {
                push(operatorStack, queue[i]);
                e++;
            } else {
                e--;
                pop(operatorStack, output);
                goto repeat;
            }
        } else if (queue[i].function || queue[i].parentheses == '(') {
            push(operatorStack, queue[i]);
        } else if (queue[i].parentheses == ')') {
            repeat1:
            if(lastElement(operatorStack).parentheses == '\0') {
                pop(operatorStack, output);
                if(lastElement(operatorStack).parentheses == '\0') goto repeat1;
            }
            else {
                rem(operatorStack);
                if(lastElement(operatorStack).function) {
                    pop(operatorStack, output);
                }
            }
        } else push(output, queue[i]);
        i++;
    }
        
        while(!(lastElement(operatorStack).terminator)) {
            pop(operatorStack, output);
        }
}
void rem(token stack[]) {
    unsigned i = 0;
    while (stack[i].terminator == false) {
        i++;
    }
    if(i>0) stack[i-1] = (token){0, '\0', 0, '\0', '\0', true};
}

double evaluate(char* string) {
    token stack[1000], queue[1000];
    unsigned i = 0;
    token operand1, operand2;
    for (unsigned e = 0; e < 1000; e++) {
        stack[e] = (token){0, '\0', 0, '\0', '\0', true};
    }
    postfix(string, queue);
    while (queue[i].terminator == false) {
        if (queue[i].value) {push(stack, queue[i]);}
        else if(queue[i].opr) {
            operand2 = lastElement(stack);
            rem(stack);
            operand1 = lastElement(stack);
            rem(stack);
            switch (queue[i].opr) {
                case '+':
                operand1.value += operand2.value;
                break;
                case '-':
                operand1.value -= operand2.value;
                break;
                case '*':
                operand1.value = operand2.value * operand1.value;
                break;
                case '/':
                operand1.value /= operand2.value;
                break;
                case '^':
                operand1.value = pow(operand1.value, operand2.value);
                break;
            }
            push(stack, operand1);
        } else {
            operand1 = lastElement(stack);
            rem(stack);
            switch (queue[i].function) {
                case 'c':
                //operand1.value = cos(operand1.value);
                break;
                case 's':
                //operand1.value = sin(operand1.value);
                break;
                case 't':
                //operand2.value = tan(operand1.value);
                case '!':
                //intructions to check if the opeand is an integer are to be added 
                // operand1.value = factorial(operand1.value);
                break;
                case 'S':
                // operand1.value = sqrt(operand1.value);
                break;
                case 'l':
                // operand1.value = ln(operand1.value);
                break;
                case 'n':
                // operand1.value = -operand1.value;
                break;
            }
            push(stack, operand1);
        }
        i++;
    }
    return stack[0].value;
}
