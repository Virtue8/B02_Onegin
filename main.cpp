// To-do
// 1 gitignore
// 3 в charcomporator ты не правильно адресуешься к переменной text, также при вызове charcomporator передаешь неверное значение.
// 4 в вызове stringsorter также неверно передается text. Сама функция принимает одномерный массив, а ты передаешь указатель на двумерный массив.
// 5 расставь assertы
// 6 исправь все ошибки, сделай рабочую сортировку пузырьком для статического массива и будем переходить дальше



//------------------------ Libraries and Files --------------------------//

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <TXLib.h>

//---------------------- Functions Initialization -----------------------//

void StringSorter (char *text, int *index, int t_height, int t_length);
char CharComparator (int i, int j, char *text);

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

    StringSorter (&text[0][0], index, t_height, t_length);
}

//--------------------------- Other functions --------------------------//

void StringSorter (char *text, int *index, int t_height, int t_length)
{
    int BubbleSortCriteria = REPEAT;

    while (BubbleSortCriteria == REPEAT)
    {
        BubbleSortCriteria = RIGHT;

        for (int i = 0; i < t_height - 1; i++)
        {
            for (int j = 0; j < t_length - 1; j++)
            {
                int CCV = CharComparator (i, j, &text[0][0]);

                if (CCV == LESSER)
                {
                    int temp_sloth = index[i];
                    index[i] = index[i+1];
                    index[i+1] = temp_sloth;
                    break;
                    BubbleSortCriteria = REPEAT;
                }
                else
                    continue;
            }
        }
    }
}

//----------------------------------------------------------------------//

int CharComparator (int i, int j, char *text)
{
    if (text[i][j] > text[i+1][j])
        return BIGGER;
    else if (text[i][j] < text[i+1][j])
        return LESSER;
    else
        return EQUAL;

    return 0;
}
