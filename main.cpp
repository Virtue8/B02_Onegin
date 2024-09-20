
//------------------------ Libraries and Files --------------------------//

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <TXLib.h>

#define FILENAME text.txt

//------------------------ Main Functions Init --------------------------//

FILE * FileOpener (const char * file_name);
size_t FileReader (FILE * file_onegin);
void Sorter (char ** text);
void Output ();
int CharComparator (char x, char y);

//----------------------- Constants and Structs -------------------------//

const char * file_name = "text.txt"

/*
struct Onegin
{
    FILE * file_onegin = NULL;
    size_t file_size = 0;
    char ** all_chars = 0;

    size_t lines_amount = 0;

    struct Line line_data = NULL;
};

struct Line
{
    size_t line_len = 0;
    char * line_place = 0;
};
*/

//-------------------------------- main ---------------------------------//

int main ()
{
    FileOpener (file_name)
}

//--------------------------- Other functions --------------------------//

FILE * FileOpener (const char * file_name)
{
    FILE * file_onegin = fopen (file_name, "r");
    if (file_onegin == NULL)
    {
        printf ("Incorrect Input!\n");
        exit ();
    }
    else
        return file_onegin;
}

//---------------------------------------------------------------------//

size_t FileReader (FILE * file_onegin)
{
    fseek (file_onegin, 0, SEEK_SET);
    file_size = fscanf (file_onegin);

    char * all_chars = (char *) calloc (file_onegin, file_size);

    // missing: getting all info for structs
    // (not introduced yet, but the same parameters must be got here)
}

// missing: Sorter, Output

//----------------------------------------------------------------------//

void Sorter (char ** text)
{

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
    .
}
