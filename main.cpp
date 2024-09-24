
//------------------------ Libraries and Files --------------------------//

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <TXLib.h>
#include <stdlib.h>
#include <sys/stat.h>

//------------------------ Main Functions Init --------------------------//

void FileReader (struct Onegin * oneg);
void LineSeparator (struct Onegin * oneg);
void Sorter (struct Onegin * oneg);
void FileWriter (struct Onegin * oneg);

//----------------------- Constants and Structs -------------------------//

struct Onegin
{
    FILE * file_onegin = NULL;                         // source file
    const char *FILE_NAME = NULL;                      // name of the source file

    size_t file_size = 0;                              // size of the source file
    char * buffer = NULL;                              // buffer with data
    char * line_ptrs = NULL;                           // buffer line pointers

    size_t lines_amount = 0;                           // amount of lines in the source file
};

//-------------------------------- main ---------------------------------//

int main ()
{
    assert (oneg != NULL);

    Onegin oneg = {};
    oneg.FILE_NAME = "text.txt";

    FileReader (&oneg);
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
    size_t ReadStatus = fread (oneg.buffer, sizeof(char), oneg.file_size, oneg.file_onegin);
    assert (ReadStatus != ferror);
    fclose (oneg.FILE_NAME);
}

//----------------------------------------------------------------------//

void LineSeparator (struct Onegin * oneg)
{
    assert (oneg != NULL);

    oneg.lines_amount = 1;
    *(oneg.buffer + oneg.file_size + 1) = '\0';

    for (int i = 0; i != oneg.file_size + 1; i++)
    {
        if (*(oneg.buffer + i) == '\n')
        {
            *(oneg.buffer + i - 1) = '\0';
            oneg.lines_amount++;
        }
    }
}

//----------------------------------------------------------------------//

void Sorter (struct Onegin * oneg)
{
    assert (oneg != NULL);

    char * oneg.line_ptrs = (char *) calloc (oneg.lines_amount, sizeof(char));
    assert (oneg.line_ptrs != NULL);
    *oneg.line_ptrs = *oneg.buffer;
    int current_line = 0;

    for (int i = 0; i < oneg.file_size; i++)
    {
        if (*(oneg.buffer + i) == '\n')
        {
            current_line++;
            *(oneg.line_ptrs + current_line) = *(oneg.buffer + i + 1);
        }
    }
}

//----------------------------------------------------------------------//

void FileWriter (struct Onegin * oneg)
{
    assert (oneg != NULL);

    output_file = fopen ("output.txt", "r");

    for (int i = 0; i < oneg.lines_amount, i++)
    {
        size_t ReadStatus = fwrite (oneg.buffer, sizeof(char), oneg.file_size, output_file);
        assert (ReadStatus != oneg.file_size);
    }

    fclose (oneg.FILE_NAME);
}
