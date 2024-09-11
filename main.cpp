
//------------------------ Libraries and Files --------------------------//

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <TXLib.h>

//---------------------- Functions Initialization -----------------------//

void StringSorter (char *text, int *index, int t_height, int t_length);
char CharComparator (int i, int j, char *text);  //

//----------------------------- Constants -------------------------------//

enum CharState
{
    EQUAL  = 'e',
    BIGGER = 'b',
    LESSER = 'l'
    //        a
    //        n
};

enum BubbleSortStates
{
    REPEAT = 'r',
    TRU   = 't'
};

//-------------------------------- main ---------------------------------//

int main ()
{
    const int t_height = 6;
    const int t_length = 7;

    int index[] = {0, 1, 2, 3, 4, 5};
    char text[t_height][t_length] = {"my",
                                     "when",
                                     "he",
                                     "and",
                                     "his",
                                     "and"};

    StringSorter (&text, &index, t_height, t_length);
}

//--------------------------- Other functions --------------------------//

void StringSorter (char *text, int *index, int t_height, int t_length)
{
    char BubbleSortCriteria = REPEAT;

    while (BubbleSortCriteria == REPEAT)
    {
        BubbleSortCriteria = TRU;
        for (int i = 0; i < t_height - 1; i++)
        {
            for (int j = 0; j < t_length - 1; j++)
            {
                int CCV = CharComparator (i, j, &text[t_height]);

                if (CCV == LESSER)
                {
                    int temp_sloth = index[i];
                    index[i] = index[i+1];
                    index[i+1] = temp_sloth;
                    break;
                }
                else
                    continue;
            }
        }
    }
}

//----------------------------------------------------------------------//

char CharComparator (int i, int j, char text[])
{
    if (text[i][j] > text[i+1][j])
        return BIGGER;
    else if (text[i][j] < text[i+1][j])
        return LESSER;
    else
        return EQUAL;

    return 0;
}
