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
    // TODO: implement a searching algorithm
    for (int i = 0; i <n; i++)
    {
        if (values[i] == value)
            return true;
    }
    return false;
}

/**
 * Sorts array of n values.
 */
 
void swap (int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;    
}

void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm, selection sort
    int min = values[0];
    int j = 0;
    
    for (int i =0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (values[i]> values[j])
            {
                swap(&values[i], &values[j]);
                min = values[j];
            }
            
            else
            {
                min = values[i];
            }
        }
          
    } 
    return;
}
