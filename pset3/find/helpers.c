/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    int first, last, mid;   
    // binary seach implementation
    if (n < 0)
    {
        return false;
    }
    else
    {   
        // Get our bounds
        first = 0;
        last = n - 1;
        mid = (first + last) / 2;
        
        // loop via while, update bounds and search again
        while (first <= last)
        {
            if (values[mid] < value)
                first = mid + 1;
            else if (values[mid] == value)
                {
                return true;
                break;
                }
            else
                last = mid - 1;
            
            mid = (first + last) / 2;
        }
    }   
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // Selection sort algorithm implemented 
    int i, j, min, tmp;
    for (i = 0; i < n; i++)
    {   
        for (j = i, min = i; j < n; j++)
        {
            if (values[j] < values[min])
            {
                min = j;
            }
        }
        tmp = values[i];
        values[i] = values[min];
        values[min] = tmp;
    }
    // below is for testing
    // for (int z = 0; z < n; z++)
    //    printf("%d\n", values[z]);
    // return;
}
