//to-do
// fread stuff
// funcs pointers

//q:
//1) charcomparator value
//2) switch in SS
//3) more simple bubblesort


//------------------------ Libraries and Files --------------------------//

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <TXLib.h>

//---------------------- Functions Initialization -----------------------//

void StringSorter (int t_height, int t_length, char text[][7], int index[]);
int CharComparator (char x, char y);
void Output (char text[][7], int index[]);

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
    char text[t_height][t_length] = {"meat",
                                     "s",
                                     "xerox",
                                     "and",
                                     "when",
                                     "ant"};

    StringSorter (t_height, t_length, text, index);

    Output(text, index);
}

//--------------------------- Other functions --------------------------//

void StringSorter (int t_height, int t_length, char text[][7], int index[])
{
    int BubbleSortCriteria = REPEAT;
    char x = '\0';
    char y = '\0';

    while (BubbleSortCriteria != RIGHT)
    {

        BubbleSortCriteria = RIGHT;

        for (int i = 0; i <= t_height + 1; i++)
        {
            for (int j = 0; j <= t_length + 1; j++)
            {
                x = text[index[i]][j];
                y = text[index[i+1]][j];

                int CCV = CharComparator (x, y);

                if (CCV == LESSER)
                {
                    int temp_sloth = index[i];
                    index[i] = index[i+1];
                    index[i+1] = temp_sloth;
                    BubbleSortCriteria = REPEAT;
                    break;
                }
                else if (CCV == EQUAL)
                    continue;
                else
                    break;
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

//----------------------------------------------------------------------//

void Output (char text[][7], int index[])
{
    for (unsigned int i = 0; i <= sizeof(index) + 1; i++)
        printf ("%d %s\n", i + 1, text[index[sizeof(index) + 1 - i]]);
}
