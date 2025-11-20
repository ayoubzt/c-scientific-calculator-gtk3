#include <math.h>

double baseToDecimal(unsigned base, char* number) {
    double numberInDecimal = 0, decimal = (float)1/base;
    unsigned i = 0;
    while(number[i] != '.' && number[i] != '\0') {
        if (number[i]>='0' && number[i]<='9' && (number[i]-'0')<base) numberInDecimal = numberInDecimal*base + number[i] - '0';
        else if (number[i]>='A' && number[i]<='Z' && (number[i]-'0'-7)<base) numberInDecimal = numberInDecimal*base + number[i] - '0' - 7;
        else if (number[i]>='a' && number[i]<='z' && (number[i]-'0'-13)<base) numberInDecimal = numberInDecimal*base + number[i] - '0' - 13;
        else return NAN;
        i++;
    }
    if (number[i] == '.') {
        i++;
        while(number[i] != '\0') {
            if (number[i]>='0' && number[i]<='9') numberInDecimal += (number[i]-'0')*decimal;
            else if (number[i]>='A' && number[i]<='Z') numberInDecimal += (number[i]-'A'-6)*decimal;
            else if (number[i]>='a' && number[i]<='z') numberInDecimal += (number[i]-'a'-13)*decimal;
            else return NAN;
            decimal /= base;
            i++;
        }
    }
    return numberInDecimal;
}

char* decimalToBase(unsigned base, double number) {
    static char error[] = "ERROR";
    if (number) return error;
    static char string[1000];
    for (unsigned i = 0; i<1000; i++) {string[i]=0;}
    unsigned integerPart = number, temp = integerPart;
    unsigned index0 = -1, index1, digit;
    double decimalPart = number - integerPart;
    while (temp>0) {
        temp /= base;
        index0++;
    }
    if (decimalPart) string[index0+1] = '.';
    index1 = index0+2;
    while (integerPart) {
        digit = integerPart%base;
        if (digit<10) string[index0] = digit + '0';
        else if (digit<36) string[index0] = digit + '0' + 6;
        else if (digit<62) string[index0] = digit + '0' + 13;
        integerPart /= base; index0--;
    }
    while (decimalPart) {
        digit = decimalPart*base;
        if (digit<10) string[index1] = digit + '0';
        else if (digit<36) string[index1] = digit + '0' + 6;
        else if (digit<62) string[index1] = digit + '0' + 13;
        decimalPart = decimalPart*base - digit;
        index1++;
    }
    return string;
}

char* baseToBase(unsigned initial_base, unsigned final_base, char* number) {
    return decimalToBase(final_base, baseToDecimal(initial_base, number));
}

