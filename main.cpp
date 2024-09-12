// To-do
// 5 asserts
// 6 bubblesort



//------------------------ Libraries and Files --------------------------//

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <TXLib.h>

//---------------------- Functions Initialization -----------------------//

void StringSorter (char text, int *index, int t_height, int t_length);
int CharComparator (char x, char y);

//----------------------------- Constants -------------------------------//

enum CharState
{
    EQUAL,
    BIGGER,
    LESSER
};

enum BubbleSortStates
{
    REPEAT,
    RIGHT
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

    StringSorter (*text[t_height], index, t_height, t_length);
}

//--------------------------- Other functions --------------------------//

void StringSorter (char text, int *index, int t_height, int t_length)
{
    int BubbleSortCriteria = REPEAT;
    char x = '\0';
    char y = '\0';

    while (BubbleSortCriteria == REPEAT)
    {
        BubbleSortCriteria = RIGHT;

        for (int i = 0; i < t_height - 1; i++)
        {
            for (int j = 0; j < t_length - 1; j++)
            {
                x = text[i][j];
                y = text[i+1][j];

                int CCV = CharComparator (x, y);

                if (CCV == LESSER)
                {
                    int temp_sloth = index[i];
                    index[i] = index[i+1];
                    index[i+1] = temp_sloth;
                    BubbleSortCriteria = REPEAT;
                    break;
                }
                else
                    continue;
            }
        }
    }
}

//----------------------------------------------------------------------//

int CharComparator (char x, char y)
{
    if (x > y)
        return BIGGER;
    else if (x < y)
        return LESSER;
    else
        return EQUAL;

    return 0;
}
