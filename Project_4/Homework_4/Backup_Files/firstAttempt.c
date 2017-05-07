// Do the words include the space at the end??? => i need to fix this

#include <stdio.h>
#include <stdlib.h>

#define SP ' '

/*void increaseLetterArraySize(char *letters)
{
    char *resizeLetterArray = realloc(letters, (letterCount + 2) * sizeof(char));
    if(ferror(stdin))
        exit(1);
    letters = resizeLetterArray;
}

void increaseWordArraySize(char **words)
{
    char **resizeWordArray = realloc(words, (2 * sizeof(MAX_WORD_ARRAY_SIZE)) *
                                     sizeof(char *));
    if(ferror(stdin))
        exit(1);
    words = resizeWordArray;
}*/

int frobcmp(char const *a, char const *b)
{
    char afrob = *a ^ 42;
    char bfrob = *b ^ 42;
    
    if (*a == ' ' && *b == ' ')
        return 0;
    else if (*a == ' ' || (afrob < bfrob))
        return -1;
    else if (*b == ' ' || (bfrob < afrob))
        return 1;
}

int compareWords(const void* a, const void* b)
{
    return frobcmp(*((const char **) a), *((const char **) b));
}

/*int addWordToList(char **words, const char *words, size_t wordLength)
{
    
}*/

int main()
{
    //Create the letter and word arrays
    char *letterArray = (char *)malloc(sizeof(char));
    char **wordArray = (char **)malloc(sizeof(char *));
    
    //Create the letter and word counters
    size_t letterCount = 0;
    size_t wordCount = 0;
    
    //Create two variables to keep track of the current and next letter from STDIN
    char currentLetter = getchar();
    if(ferror(stdin))
        exit(1);
    char nextLetter = getchar();
    if(ferror(stdin))
        exit(1);
    
    //Possibilities:
    //1. Both curr and next are valid ==> finished
    //2. Both curr and next are space characters (remove the extra spaces) => finished
    //3. Curr is valid, but next is a space character(end of word) => i think this one is the base case
    //4. Curr is space character, and next is EOF ==> finished
    //5. Curr is valid, and next is EOF (no space, so must include one) ==> finished
    //6. Curr is space character, and next is valid => finished
    while (currentLetter != EOF)
    {
        if(ferror(stdin))
            exit(1);
        
        letterArray[letterCount++] = currentLetter;
        //increaseLetterArraySize(letterArray);
        char* temp = realloc(letterArray, ((letterCount + 2) * sizeof(char)));
        letterArray = temp;
        
        if (currentLetter != SP && nextLetter == EOF)
        {
            currentLetter = SP;
            continue;
        }
        else if (currentLetter == SP && nextLetter == EOF)
        {
            //letterArray[letterCount++] = currentLetter;
            wordArray[wordCount++] = letterArray;
            //increaseWordArraySize(wordArray);
            char** temp2 = realloc(wordArray, (wordCount + 2) * sizeof(char *));
            wordArray = temp2;
            
            letterArray = NULL;
            letterCount = 0;
            letterArray = (char *)malloc(sizeof(char));
            
            currentLetter = nextLetter;
            continue;
        }
        else if (currentLetter == SP && nextLetter == SP)
        {
            while (nextLetter == SP)
            {
                currentLetter = nextLetter;
                nextLetter = getchar();
                if(ferror(stdin))
                    exit(1);
            }
            
            //letterArray[letterCount++] = currentLetter;
            wordArray[wordCount++] = letterArray;
            //increaseWordArraySize(wordArray);
            char** temp2 = realloc(wordArray, (wordCount + 2) * sizeof(char *));
            wordArray = temp2;
            
            letterArray = NULL;
            letterCount = 0;
            letterArray = (char *)malloc(sizeof(char));
        }
        else if (currentLetter == SP && nextLetter != EOF)
        {
            //letterArray[letterCount++] = currentLetter;
            wordArray[wordCount++] = letterArray;
            //increaseWordArraySize(wordArray);
            char** temp2 = realloc(wordArray, (wordCount + 2) * sizeof(char *));
            wordArray = temp2;
            
            letterArray = NULL;
            letterCount = 0;
            letterArray = (char *)malloc(sizeof(char));
        }
            
        
        currentLetter = nextLetter;
        nextLetter = getchar();
        if(ferror(stdin))
            exit(1);
    }
    
    qsort(wordArray, wordCount, sizeof(char *), compareWords);
    
    for (size_t i = 0; i < wordCount; i++)
    {
        for (size_t j; ; j++)
        {
            putchar(wordArray[i][j]);
            if(wordArray[i][j] == ' ')
                break;
        }
    }
    
    for (size_t i = 0; i < wordCount; i++)
    {
        free(wordArray[i]);
    }
    
    free(wordArray);
    
    exit(0);
    
    
}
