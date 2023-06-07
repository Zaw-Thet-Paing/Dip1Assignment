#include <stdio.h>
#include <string.h>

void findWord(char *word);

int main()
{
    findWord("winhtut");
    findWord("NationalCyberCity");
    return 0;
}

void findWord(char *word)
{
    FILE *fptr;
    char string[50];

    fptr = fopen("assignment4.txt", "r");

    if (fptr == NULL)
    {
        printf("File cannot open\n");
        return;
    }
    else
    {
        int wordCount = 0;
        while (!feof(fptr))
        {
            fscanf(fptr, "%s", string);
            if (strcmp(string, word) == 0)
            {
                wordCount++;
            }
        }

        if (wordCount > 0)
        {
            printf("We found \"%s\" for %d time\n", word, wordCount);
        }
    }
}