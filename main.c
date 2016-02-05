/*
 * Created by Joaquin Castro
 * Base file
*/


#include <stdio.h>
int calculateECount(int input[1025]);


int main (int argc, char *argv[])
{
    int arrayHolder[27][1025];
    int currentArray[1025];
    int eCountForArrays[27];
    int key = 0;
    int i = 0;
    int c = 0;
    int currentChar = 0;
    int previousChar = 0;
    int previousCharHolder = 0;
    int highestECount = 0;
    int secondHighestECount = 0;
    int outputArray[1025];
    int originalArray[1025];
    int j =0;


    //initialize all the registers
    for(i = 0; i < 27; i++){
        for(j = 0; j < 1025; j++){
            arrayHolder[i][j] = 0;
        }
        eCountForArrays[i] = 0;
    }

    //initialize rest of the arrays
    for(i = 0; i < 1025; i++){
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

    //replaces the new line, feed line, with 0
    for (i = 0; i < 1025; i++) {
        if(currentArray[i] == 10) {
            currentArray[i] = 0;
            originalArray[i] = 0;
        }
    }

    //Decyphers the original array for every key given
    for(key = 0; key < 27; key++){
        for(i = 0; i < 1025; i++){
            if(currentArray[i] == 0)
                break;
            else
                currentChar = currentArray[i];

            //go to upper case
            if (currentChar >= 97 && currentChar <= 122)
                currentChar =  (currentChar - 32);

            //go to base value
            if (currentChar % 64 >= 1 && currentChar % 64 <= 26)
                currentChar =  (currentChar - 64);
            else
                currentChar = 0;

            //removing previous character
            previousCharHolder = currentChar;
            currentChar = currentChar - previousChar - (key % 27);
            previousChar = previousCharHolder;

            while (currentChar < 0) {
                currentChar = 27 + currentChar;
            }
            //prints out message
            if (currentChar == 0)
                currentArray[i] = 32;
            else
                currentArray[i] = (currentChar + 64);
        }

        ///places the deciphered array in the list of ALL deciphered arrays
        for(i = 0; i < 1058; i++){
            if(currentArray[i] == 0)
                break;
            arrayHolder[key][i] = currentArray[i];
        }

        //resets the currentArray back to the original so we can decode with different key
        for(j = 0; j < 1025; j++){
            currentArray[j] = originalArray[j];
        }
    }

    //calculates the E count for each array in the list of ALL arrays
    for(i = 0; i < 27; i++){
        eCountForArrays[i] = calculateECount(arrayHolder[i]);
    }


    //checks to find the 2nd highest E count
    //TODO: Make sure this is the same as Dr. Brylows
    for(i = 0; i < 27; i++){
        if(i != 0) {
            if(eCountForArrays[i] > eCountForArrays[highestECount]){
                secondHighestECount = highestECount;
                highestECount = i;
            }else if( eCountForArrays[i] > eCountForArrays[secondHighestECount])
                secondHighestECount = i;
        }
    }

    printf("most likely key is: %d\n", secondHighestECount);

    //copies over the characters from the key guess to the output array
    for (i = 0; i < 1025; i++) {
        if(arrayHolder[secondHighestECount][i] == 0)
            break;
        outputArray[i] = arrayHolder[secondHighestECount][i];
    }

    //Attemps to print out the characters in the output array
    //For some reason only the new line will allow this to print
    for(i = 0; i < 1025; i++){
        if(outputArray[i] == 0)
            break;
        if(outputArray[i] != 0)
            printf("%c", outputArray[i]);
    }
}

int calculateECount(int input[1025]){
    int counter = 0;
    int numberOfE = 0;
    int sentence[1025];

    for(counter = 0 ; counter < 1025; counter++){
        sentence[counter] = input[counter];
    }

    for(counter = 0; counter < 1025; counter++){
        if(input[counter] == 0){
            break;
        }
        if(input[counter] == 'E'){
            numberOfE = numberOfE + 1;
        }
    }
    return numberOfE;
}