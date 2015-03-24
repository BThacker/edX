#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[0])
{
    int k = 0;
    // Confirm theres a command line argument, if not, crash
    if (argc != 2)
    {
        printf("We need one argument, a key. No more, no less!\n");
        return 1;
    }
    else
    {
        k = atoi(argv[1]);
    }
    // Get phrase to encrypt
    string phrase = GetString();
    int cipher = 0;
    for(int i = 0; i < strlen(phrase); i++)
    {            
        // handle various input scenarios
        if (isalpha(phrase[i]) && isupper(phrase[i]))
        {
            // If needed, WRAP
            if ((phrase[i] - 65 + k) > 25)
            {
                cipher = ((phrase[i] - 65 + k) % 26 + 65);
                printf("%c", cipher);  
            }
            else
            {
                cipher = (phrase[i] + k);
                printf("%c", cipher);
            }
        }
        // if lowercase 
        if (isalpha(phrase[i]) && islower(phrase[i]))
        {
            if ((phrase[i] - 97 + k) > 25)
            {
                cipher = ((phrase[i] - 97 + k) % 26 + 97);
                printf("%c", cipher);
            }
            else
            {
                cipher = (phrase[i] + k);
                printf("%c", cipher);
            }  
        }
        // handle extreme cases
        if (!isalpha(phrase[i]))
        {
            cipher = (phrase[i]);
            printf("%c", cipher);
        }
    }
    // print line break to display properly
    printf("\n");
    
}

