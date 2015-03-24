#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>

int main(void)
{
    // initialize variables for program
    string name = GetString();
    printf("%c", toupper(name[0]));
    for (int i = 0; i < strlen(name); i++)
    {
        // Check to see if a space is present, if so, print the first initial
        // after the space 
        if (name[i] == ' ')
        {
            printf("%c", toupper(name[i + 1]));
        }
        else
        {
            continue;
        }
    }
    printf("\n");
}
