#include <stdio.h>
#include <stdbool.h>
typedef struct token token;
struct token {
    double value;
    char opr;
    unsigned precedence;
    bool function;
    char parentheses;
    bool terminator;
};



void tok(char *string, token token[]) {
    unsigned i = 0, e = 0;
    double r = 1;
    for (int i = 0; i<1000; i++) {
    token[i].value = 0;
    token[i].opr = '\0';
    token[i].precedence = 0;
    token[i].function = false;
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
            token[e].opr = string[i];
            token[e].terminator = false;
            switch (string[i]) {
                case '+':
                case '-':
                    token[e].precedence = 1;
                    break;
                case '*':
                case '/':
                    token[e].precedence = 2;
                    break;
                case '^':
                    token[e].precedence = 3;
                    break;
                case '(':
                    token[e].parentheses = '(';
                    token[e].opr = '\0';
                    break;
                case ')':
                    token[e].parentheses = ')';
                    token[e].opr = '\0';
                    break;
                
                case 's':
                case 'c':
                case 't':
                case '!':
                case 'S':
                    token[e].function = true;
                    token[e].opr = '\0';
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
                src[index] = (token){0, '\0', 0, false, '\0', true};
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
    token operatorStack[1000], queue[1000], dump[1000];
    unsigned i = 0, e;
    for (int e = 0; e < 1000; e++) {
        queue[e] = operatorStack[e] = output[e] = dump[e] = (token){0, '\0', 0, false, '\0', true};
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
            pop(operatorStack, output);
            if(lastElement(operatorStack).parentheses) {
                pop(operatorStack, dump);
                if(lastElement(operatorStack).function) {
                    pop(operatorStack, output);
                }
            }
            else goto repeat1;
        } else push(output, queue[i]);
        i++;
    }
        
        while(!(lastElement(operatorStack).terminator)) {
            pop(operatorStack, output);
        }
}
