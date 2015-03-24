#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // request height from the user

    printf("Height: ");
    //declare all relevent variables

    bool height_valid = false;
    int height;

    // get and validate user input via a loop

    while (height_valid == false)
    {
        height = GetInt();
        if (height >= 0 && height <= 23)
        {
            height_valid = true;
        }
        else
        {
            printf("Retry: ");
        }
    }

    // format and print our board based on the pset description
    for (int i = 0; i < height; i++)
    {
        for (int space = i; space < height - 1; space++)
        {
            printf(" ");
        }
        
        for (int hash = 0; hash < i + 2; hash++)
        {
            printf("#");
        }     
        printf("\n");
    }
}
