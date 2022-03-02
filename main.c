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

const int8_t BUFFERS_SIZE = 10;
int main(void)
{
    os_ClrHome();
    char inputBase[3];
    os_GetStringInput("What is input base? ", inputBase, BUFFERS_SIZE);
    int baseIn = atoi(inputBase);
    if(baseIn < 2 || baseIn > 36)
       return 0;
    os_ClrHome();
    char outputBase[3];
    os_GetStringInput("What is output base? ", outputBase, BUFFERS_SIZE);
    int baseOut = atoi(outputBase);
    if(baseOut < 2 || baseOut > 36)
       return 0;
    char bufferForSize[3];
    os_ClrHome();
    os_GetStringInput("Size of number? ", bufferForSize, BUFFERS_SIZE);
    int inputSize = atoi(bufferForSize);
    char inputNumber[inputSize+1];
    os_ClrHome();
    printText("Enter number to convert: ", 0, 0);
    os_GetStringInput( " ", inputNumber, BUFFERS_SIZE);
    os_ClrHome();
    printText(inputNumber, 0, 0);
    while(!os_GetCSC());
    os_ClrHome();
    int inDec = toDecimal(inputNumber, baseIn, inputSize);
    char outputBuffer[10];
    sprintf(outputBuffer, "%d", inDec);

    os_ClrHome();
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
    int remainder = quotient % baseOut;
        quotient = (quotient-remainder)/baseOut;
        actualOutput[counter++] = alphabet[remainder];
    char theRealOutput[counter];
    for(int i = 0; i < counter; i++)
    {
        theRealOutput[i] = actualOutput[counter-(i+1)];
    }
    printf("%.*s", counter, theRealOutput);
    while(!os_GetCSC());
    return 0;
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
    while(!os_GetCSC());
    return output;
}

void printText(const char *text, uint8_t xpos, uint8_t ypos)
{
    os_SetCursorPos(ypos, xpos);
    os_PutStrFull(text);
}
