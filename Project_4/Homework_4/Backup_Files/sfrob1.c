// Do the words include the space at the end??? => i need to fix this

#include <stdio.h>
#include <stdlib.h>

#define SP ' '

char fetchCharacter();
int frobcmp(char const *a, char const*b);
int compareWords(const void* a, const void* b);
void writeOutput(char **finalWordArray, size_t numWords);
void freeArrays(char **finalWordArray, char *finalLetter, size_t numWords);

int main()
{
    //Create the letter and word arrays
    char *letterArray = (char *)malloc(sizeof(char));
    char **wordArray = (char **)malloc(sizeof(char *));
    
    //Create the letter and word counters
    size_t letterCount = 0;
    size_t wordCount = 0;
    
    //Create two variables to keep track of the current and next letter from STDIN
    char currentLetter = fetchCharacter();
    char nextLetter = fetchCharacter();
    
    //Keep reading until the file ends
    while (currentLetter != EOF)
    {
        if(ferror(stdin))
            exit(1);
        
        //Add a character to the letter array, and resize with each new char
        letterArray[letterCount++] = currentLetter;
        char* newLetterArray = realloc(letterArray, ((letterCount + 1) *
                                     sizeof(char)));
        letterArray = newLetterArray;
        
        //If a space is reached, then put the word in the word array, and resize
        if (currentLetter == SP)
        {
            wordArray[wordCount++] = letterArray;
            char** newWordArray = realloc(wordArray, ((wordCount + 1) *
                                          sizeof(char *)));
            wordArray = newWordArray;
            
            //Reset the letter array
            letterArray = NULL;
            letterArray = (char *)malloc(sizeof(char));
            letterCount = 0;
        }
        
        //If there is a proper space at the EOF, and EOF is reached, then done
        if (currentLetter == SP && nextLetter == EOF)
        {
            break;
        }
        //If the EOF is missing a space character, then add one as requested
        else if (currentLetter != SP && nextLetter == EOF)
        {
            currentLetter = SP;
            continue;
        }
        //If there is a line with multiple spaces in a row, then remove them
        else if (currentLetter == SP && nextLetter == SP)
        {
            while (nextLetter == SP)
            {
                currentLetter = nextLetter;
                nextLetter = fetchCharacter();
            }
            continue;
        }
        
        //Normal Scenario: Both currentLetter and nextLetter are valid chars
        currentLetter = nextLetter;
        nextLetter = fetchCharacter();
    }

    //Sort the output
    qsort(wordArray, wordCount, sizeof(char *), compareWords);
    
    //Write the output after the words are all collected
    writeOutput(wordArray, wordCount);
    
    //Free memory
    freeArrays(wordArray, letterArray, wordCount);
    
    exit(0);
}

//getchar() with error check
char fetchCharacter()
{
    char newCharacter = getchar();
    if(ferror(stdin))
        exit(1);
    return newCharacter;
}

int frobcmp(char const *a, char const *b)
{
    char afrob, bfrob;
    for (;; a++, b++)
    {
        afrob = *a ^ 42;
        bfrob = *b ^ 42;
        if (*a == SP && *b == SP)
            return 0;
        else if (*a == SP || (afrob < bfrob))
            return -1;
        else if (*b == SP || (bfrob < afrob))
            return 1;
    }
}

//Properly format parameters for qsort
int compareWords(const void* a, const void* b)
{
    return frobcmp(*((const char **) a), *((const char **) b));
}

//Write output until the space char is hit (i.e. EOF)
void writeOutput(char **finalWordArray, size_t numWords)
{
    for (size_t i = 0; i < numWords; i++)
    {
        for (size_t j = 0; ; j++)
        {
            putchar(finalWordArray[i][j]);
            if(finalWordArray[i][j] == ' ')
                break;
        }
    }
}

//Free memory
void freeArrays(char **finalWordArray, char *finalLetterArray, size_t numWords)
{
    for (size_t i = 0; i < numWords; i++)
    {
        free(finalWordArray[i]);
    }
    free(finalWordArray);
    free(finalLetterArray);
}

