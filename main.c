#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
const char alphabet[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";


int indexOf(char c);
int toDecimal(char* input, int base, uint8_t size);
void printText(const char *text, uint8_t xpos, uint8_t ypos);
int getIntInput(char* msg, int8_t min, int8_t max);


int indexOf(char c)
{
    c = toupper(c);
    for(int i = 0; i < 36; i++)
    {
        if(alphabet[i] == c)
            return i;
    }
    return -1;
}


int toDecimal(char* input, int base, uint8_t size)
{
    int output = 0;
    for(int i = 0; i < size; i++)
    {
        int ii = indexOf(input[size-(i+1)]);
        if(ii < base && ii > -1)
            output += ii * pow(base, i);
    }
    return output;
}

void printText(const char *text, uint8_t xpos, uint8_t ypos)
{
    os_SetCursorPos(ypos, xpos);
    os_PutStrFull(text);
}

int getIntInput(char* msg, int8_t min, int8_t max)
{
	os_ClrHome();
	char input[3];
    os_GetStringInput(msg, input, 10);
    int inputInt = atoi(input);
    if(inputInt < min || inputInt > max)
	{
       pgrm_CleanUp();
		return 0;
	}
	os_ClrHome();
	return inputInt;
}

int main(void)
{
	int baseIn = getIntInput("What is input base? ", 2, 36);
	int baseOut = getIntInput("What is output base? ", 2, 36);
	int inputSize = getIntInput("Size of number? ", 1, 12);
    char inputNumber[inputSize+1];
    printText("Enter number to convert: ", 0, 0);
    os_GetStringInput(" ", inputNumber, 12);
    os_ClrHome();
    int inDec = toDecimal(inputNumber, baseIn, inputSize);
    char outputBuffer[10];
    sprintf(outputBuffer, "%d", inDec);
    if(baseOut == 10)
    {
            printf("%s",outputBuffer);
        while(!os_GetCSC());
                return 0;
    }
    int quotient = inDec;
    char actualOutput[10];
    int counter = 0;
    while(quotient > 0)
    {
        int remainder = quotient % baseOut;
        quotient = (quotient-remainder)/baseOut;
        actualOutput[counter++] = alphabet[remainder];
    }
    char theRealOutput[counter];
    for(int i = 0; i < counter; i++)
    {
        theRealOutput[i] = actualOutput[counter-(i+1)];
    }
    printf("%.*s", counter, theRealOutput);
    while(!os_GetCSC());
    return 0;
}
