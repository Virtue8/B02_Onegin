
//------------------------ Libraries and Files --------------------------//

#include <stdio.h>
//#include <string.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <TXLib.h>
#include <stdlib.h>
#include <sys/stat.h>

//------------------------ Main Functions Init --------------------------//

void FileReader (struct Onegin * oneg);
void LineSeparator (struct Onegin * oneg);
void Sorter (char ** text);
void Output ();
int CharComparator (char *x, char *y);

//----------------------- Constants and Structs -------------------------//

struct Onegin
{
    FILE * file_onegin = NULL;                         // source file
    const char *FILE_NAME = NULL;                      // name of the source file

    size_t file_size = 0;                              // size of the source file
    char * buffer = NULL;                              // buffer with data

    size_t lines_amount = 0;                           // amount of lines in the source file

    struct Line * line = NULL;                         // current line data
};

struct Line
{
    size_t str_len = 0;                                // length of the line
    char * str = NULL;                                 // line pointer
};

//-------------------------------- main ---------------------------------//

int main ()
{
    assert (oneg != NULL);

    Onegin oneg = {};
    const char * oneg.file_onegin = "text.txt";

    FileReader (oneg.FILE_NAME);
    LineSeparator (&oneg);
}

//--------------------------- Other functions --------------------------//

void FileReader (struct Onegin * oneg)
{
    assert (oneg != NULL);                             // checking the right memory allocation
    assert (oneg.buffer != NULL);

    oneg.file_onegin = fopen (oneg.FILE_NAME, "r");
    assert(oneg.file_onegin != NULL);                  // source file opening

    struct stat st = {};                               // getting the file size
    fstat(fileno(oneg.file_onegin), &st);              // through fstat()
    oneg.file_size = st.st_size;
    assert (oneg.file_size != 0);

    char * oneg.buffer = (char *) calloc (oneg.file_size + 1, sizeof(char));             // reading the content
    assert (oneg.buffer != NULL);                                                        // to buffer
    ReadStatus = fread (oneg.buffer, sizeof(char), oneg.file_size, oneg.file_onegin);
    assert (ReadStatus != NULL);
    fclose (oneg.FILE_NAME);
}

//----------------------------------------------------------------------//

void LineSeparator (struct Onegin * oneg)
{
    assert (oneg != NULL);

    oneg.lines_amount = 1;

    char ** line_data_buffer = (char **) calloc (oneg.file_size + 1, sizeof(char));
    assert (line_data_buffer);

    oneg.buffer[oneg.file_size + 1] = '\0';

    for (int i = 0; i != oneg.file_size + 1; i++)
    {
        if (oneg.buffer[i] == '\n')
        {
            oneg.buffer[i-1] = '\0';
            oneg.lines_amount++;
        }
    }
}

//----------------------------------------------------------------------//

void Sorter (char ** text)
{
    assert (oneg != NULL);


}

//----------------------------------------------------------------------//

void Output (string text[t_height], int index[t_height])
{
    assert (oneg != NULL);


}
