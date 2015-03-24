#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    // declare variables, might be more than we need 
    bool input_valid = false;
    int change_int = 0;
    float change_owed = 0.0;
    int quart = 0;
    int dime = 0;
    int nick = 0;
    int penny = 0;
    int result = 0;

    // Get and validate input 
    do 
    {
        printf("How much change is owed?: ");
        change_owed = GetFloat();
        
        if (change_owed >= 0)
        {   
            change_int = (int) round(change_owed * 100);
            input_valid = true;
        }
        else
        {
            printf("Invalid, must be 0 or positive.\n");
        }
    } while (input_valid == false);
    // calculate coins remaining in a loop
    // tried one way, had to do this way to prevent rounding errors
    while (change_int >= 1)
    {
        quart = change_int / 25;
        change_int %= 25;
        
        dime = change_int / 10;
        change_int %= 10;
        
        nick = change_int / 5;
        change_int %= 5;
        
        penny = change_int / 1;
        change_int %= 1;
    } 
    // produce output to console
    result = (quart + dime + nick + penny);
    printf("%i", result);   
    printf("\n");
}
