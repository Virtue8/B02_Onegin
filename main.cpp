
//ZZN advice:
//
//char * all_chars (calloc(sizeoffile<-fstat (sizeof (char) !))) ask SDS
//fread to read file to all_chars, return how_many_bytes_are_read?=x
// num of strs  ('\n')
//        ^           char ** str_adr   (also calloc(x, sizeofunit))     pointers of strings beginnings
// '/n' to '/0' func
// also 0th str address and +1 (cause de '\0')

// then bubblesort str_adr


//------------------------ Libraries and Files --------------------------//

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <TXLib.h>

#define FILENAME text.txt

//------------------------ Main Functions Init --------------------------//

FILE * FileOpener (const char * file_stream);   // opens the stream

//     ||
//    \||/
//     \/

size_t FileSize (FILE * file);          // counts the amount of strings and meaning
                                        // chars in every string of file
//     ||
//    \||/
//     \/

void FileToArray ();                    // 1) puts the reformed content
                                        //    of the file to "text" array
//     ||                               // 2) creates "index" array with
//    \||/                              //    every string unique index
//     \/                               //    (to sort in future)

void BubbleSort (char ** text);

//     ||                               // sorts indexes according to a-z (qSort in future)
//    \||/
//     \/

void Output ();                         // writes the result in "output.txt"
                                        // (currently it outputs the data in terminal)


//---------------------- Secondary Functions Init -----------------------//

int CharComparator (char x, char y);
void Output (string text[t_height], int index[t_height]);

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
    string text[t_height] = {};
    int index[t_height] = {};
    for (int i = 0; i < t_height; i++)
        index[i] += i;                                 //makes index look like {0, 1, ..., 63}

    fread (text, sizeof (char), t_height * t_length, file);

    StringSorter (t_height, t_length, text, index);

    Output(text, index);
}

//--------------------------- Other functions --------------------------//

FILE * FileOpener ()

void BubbleSort (int t_height, int t_length, string text[t_height], int index[t_height])
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

void Output (string text[t_height], int index[t_height])
{
    for (unsigned int i = 0; i <= sizeof(index) + 1; i++)
        printf ("%d %s\n", i + 1, text[index[sizeof(index) + 1 - i]]);
}
