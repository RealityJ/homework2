/*
 * Created by Joaquin Castro
 * Base file
*/


#include <stdio.h>
//constants that define
#define ringSize 27
#define largestStringSize 1025
#define conversionToActualValue 64
#define spaceValue 32
int calculateECount(int input[largestStringSize]);


int main (int argc, char *argv[])
{
    int arrayHolder[ringSize][largestStringSize];
    int currentArray[largestStringSize];
    int eCountForArrays[ringSize];
    int key = 0;
    int i = 0;
    int c = 0;
    int currentChar = 0;
    int previousChar = 0;
    int previousCharHolder = 0;
    int highestECount = 0;
    int secondHighestECount = -1;
    int outputArray[largestStringSize];
    int originalArray[largestStringSize];
    int j =0;


    //initialize all the registers
    for(i = 0; i < ringSize; i++){
        for(j = 0; j < largestStringSize; j++){
            arrayHolder[i][j] = 0;
        }
        eCountForArrays[i] = 0;
    }

    //initialize rest of the arrays
    for(i = 0; i < largestStringSize; i++){
        currentArray[i] = 0;
        outputArray[i] = 0;
        originalArray[i] = 0;
    }

    //have to reset I here because we used it to initialize the arrays
    i=0;
    //gets the input from the user
    while((c = getchar()) != EOF )
    {
        if(c != 0) {
            currentArray[i] = c;
            originalArray[i] = c;
        }
        i++;
    }

    i = 0;
    //Decyphers the original array for every key given
    for(key = 0; key < ringSize; key++){
        previousChar = 0;
        previousCharHolder = 0;
        for(i = 0; i < largestStringSize; i++){

            if(currentArray[i] == 10){
                continue;
            }
            //saves time incase we reached the end
            if(currentArray[i] == 0)
                break;
            else
                currentChar = currentArray[i];

            //go to upper case
            if (currentChar >= 'a' && currentChar <= 'z')
                currentChar =  (currentChar - spaceValue);

            //go to base value
            if (currentChar % conversionToActualValue >= 1 && currentChar % conversionToActualValue <= (ringSize - 1))
                currentChar =  (currentChar - conversionToActualValue);
            else
                currentChar = 0;

            //removing previous character
            previousCharHolder = currentChar;
            currentChar = currentChar - previousChar - (key % ringSize);
            previousChar = previousCharHolder;

            //adds when negative
            while (currentChar < 0) {
                currentChar = ringSize + currentChar;
            }


            //prints out message
            if (currentChar == 0)
                currentArray[i] = spaceValue;
            else
                currentArray[i] = (currentChar + conversionToActualValue);
        }

        ///places the deciphered array in the list of ALL deciphered arrays
        for(i = 0; i < largestStringSize; i++){
            if(currentArray[i] == 0)
                break;
            arrayHolder[key][i] = currentArray[i];
        }

        //resets the currentArray back to the original so we can decode with different key
        for(j = 0; j < largestStringSize; j++){
            currentArray[j] = originalArray[j];
        }
    }

    //calculates the E count for each array in the list of ALL arrays
    for(i = 0; i < ringSize; i++){
        eCountForArrays[i] = calculateECount(arrayHolder[i]);
    }


    //checks to find the 2nd highest E count
    //TODO: Make sure this is the same as Dr. Brylows
    for(i = 0; i < ringSize; i++){
        if (eCountForArrays[i] > eCountForArrays[highestECount] && i != 0) {
            secondHighestECount = highestECount;
            highestECount = i;
        }
        else if (eCountForArrays[i] > eCountForArrays[secondHighestECount] && i != 0)
            secondHighestECount = i;
    }

    if(secondHighestECount == -1 || eCountForArrays[secondHighestECount] == 0){
        secondHighestECount = 0;
    }

    printf("Most probable key is %d\n", secondHighestECount);

    //copies over the characters from the key guess to the output array
    for (i = 0; i < largestStringSize; i++) {
        if(arrayHolder[secondHighestECount][i] == 0)
            break;
        outputArray[i] = arrayHolder[secondHighestECount][i];
    }

    //Attempts to print out the characters in the output array
    //For some reason only the new line will allow this to print
    for(i = 0; i < largestStringSize; i++){
        if(outputArray[i] == 0){
            printf("\n");
            break;
        }
        if(outputArray[i] != 0)
            printf("%c", outputArray[i]);
    }
}

int calculateECount(int input[largestStringSize]){
    int counter = 0;
    int numberOfE = 0;
    int sentence[largestStringSize];

    for(counter = 0 ; counter < largestStringSize; counter++){
        sentence[counter] = input[counter];
    }

    for(counter = 0; counter < largestStringSize; counter++){
        if(input[counter] == 0){
            break;
        }
        if(input[counter] == 'E'){
            numberOfE = numberOfE + 1;
        }
    }
    return numberOfE;
}
