/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        THIS LIBRARY ALLOWS TO CONVERT POSITITVE REAL NUMBERS FROM BASE TO BASE(62-2)                         
                        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                                                                                                                            */


// This function converts from a base n to base 10

double baseToDecimal(unsigned base, char* number);


// This function converts from base 10 to base n

char* decimalToBase(unsigned base, double number);


// This function converts from base n to base n'

char* baseToBase(unsigned initial_base, unsigned final_base, char* number)