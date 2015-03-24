#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char* argv[])
{
    int k = 0;
    int y = 0;
    
    // Confirm theres a command line argument, if not, crash
    if (argc != 2)
    {
        printf("We need one argument, a key. No more, no less!\n");
        return 1;
    }
    // check argument to confirm alpha, if not, crash with error
    else if (argv[1])
    {
        int len = strlen(argv[1]);
        for (int i = 0; i < len; i++)
        {
            if (!isalpha(argv[1][i]))
            {
                printf("invalid command line argument\n");
                return 1;
            }
        }
    }
    else
    {
        string key = argv[1];
        printf("%s", key);  
    }
  
    // Get phrase to encrypt
    string phrase = GetString();
    int cipher = 0;
    // int keypost = 0;
    for(int i = 0; i < strlen(phrase); i++)
    {        
        // We have to declare this variable inside here to prevent crashing
        int len1 = strlen(argv[1]);
        // logic under here for which key and character to use from the pass
        if (y >= len1)
        {
            y = 0;
        }
        if (isupper(argv[1][y]))
        {
            k = (argv[1][y]) - 65;
        }
        if (islower(argv[1][y]))
        {
            k = (argv[1][y]) - 97;
        }
        // handle various input scenarios
        
        if (isalpha(phrase[i]) && isupper(phrase[i]))
        {
            // If needed, WRAP
            if ((phrase[i] - 65 + k) > 25)
            {
                cipher = ((phrase[i] - 65 + k) % 26 + 65);
                printf("%c", cipher);
                y++;
                 
            }
            else
            {
                cipher = (phrase[i] + k);
                printf("%c", cipher);
                y++;
            }
        }
        // lowercase 
        if (isalpha(phrase[i]) && islower(phrase[i]))
        {
            if ((phrase[i] - 97 + k) > 25)
            {
                cipher = ((phrase[i] - 97 + k) % 26 + 97);
                printf("%c", cipher);
                y++;
            }
            else
            {
                cipher = (phrase[i] + k);
                printf("%c", cipher);
                y++;
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

