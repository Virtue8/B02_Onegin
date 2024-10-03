
//------------------------ Libraries and Files --------------------------//

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/param.h>

//------------------------ Main Functions Init --------------------------//

void FileReader (struct Onegin * oneg);
void LineSeparator (struct Onegin * oneg);
void Sorter (struct Onegin * oneg);
int Comparator (char * a, size_t len_a, char * b, size_t len_b);
void Swapper (struct Onegin * oneg, int i, int j);
//void FileWriter (struct Onegin * oneg);
void FileOutput (struct Onegin * oneg);

//------------------------ Secondary Functions --------------------------//

size_t GimmeFileSize (struct Onegin * oneg);
size_t BufferLinesCounter (struct Onegin * oneg);

//----------------------- Constants and Structs -------------------------//

struct Onegin
{
    FILE * file_onegin    = NULL;                      // source file
    const char *file_name = NULL;                      // name of the source file

    size_t file_size    = 0;                              // size of the source file
    char * buffer       = NULL;                           // buffer with data
    size_t lines_amount = 0;

    struct Line * line = NULL;
};

struct Line
{
    char * lines_ptr = NULL;
    int line_len  = 0;
};

//-------------------------------- main ---------------------------------//

int main ()
{
    Onegin oneg = {};
    oneg.file_name = "text.txt";

    FileReader (&oneg);
    printf("reader execution is successful\n");
    LineSeparator (&oneg);
    printf("separator execution is successful\n");
    Sorter (&oneg);
    printf("sorter execution is successful\n");
    FileOutput (&oneg);
    printf("writer execution is successful\n");

    free (oneg.buffer);
    free (oneg.line->lines_ptr);
    free (&oneg.line->line_len);
}

//--------------------------- Other functions --------------------------//

void FileReader (struct Onegin * oneg)
{
    assert (oneg != NULL);

    oneg->file_onegin = fopen (oneg->file_name, "rb");                                             // source file opening
    assert (oneg->file_onegin != NULL);

    oneg->file_size = GimmeFileSize (oneg);

    oneg->buffer = (char *) calloc ((oneg->file_size + 1), sizeof(char));                          // reading the content
    assert (oneg->buffer != NULL);                                                                 // to buffer

    size_t ReadStatus = fread (oneg->buffer, sizeof(char), oneg->file_size, oneg->file_onegin);
    if (ReadStatus != oneg->file_size)
        printf ("wrong reading\n");

    oneg->lines_amount = 1;
    *(oneg->buffer + oneg->file_size + 1) = '\0';

    fclose (oneg->file_onegin);
}

//----------------------------------------------------------------------//

void LineSeparator (struct Onegin * oneg)
{
    assert (oneg != NULL);

    oneg->lines_amount = BufferLinesCounter (oneg);                                                // counts the amount of lines in the buffer
    printf ("%d", oneg->lines_amount);

    oneg->line = (Line*) calloc (oneg->lines_amount, sizeof(Line));
    assert (oneg->line != NULL);                                                                   // line counter (local)
    int prev_i_value = -1;
    int len = 0;

    for (int i = 0; i != oneg->file_size + 1; i++)
    {
        if (*(oneg->buffer + i) == '\n')
        {
            oneg->line[i].line_len = i - prev_i_value - 2;                                         // entering line length in len data buffer (without \0 at the end)
            oneg->line[i].lines_ptr = oneg->buffer + i - oneg->line[i].line_len - 1;               // entering line pointer in ptr data buffer

            prev_i_value = i;
        }
    }
}

//----------------------------------------------------------------------//

void Sorter (struct Onegin * oneg)
{
    assert (oneg != NULL);

    char * a = NULL;
    char * b = NULL;

    int len_a = 0;
    int len_b = 0;

    for (int i = 0; i < oneg->lines_amount; i++)
    {
        for (int j = 1; j < oneg->line->line_len - i; j++)
        {
            if (Comparator(i, j, oneg) == 1)
                Swapper(oneg, i, j);
        }
    }
}

//----------------------------------------------------------------------//

int Comparator (int i, int j, struct Onegin * oneg)
{
    int k = 0;
    char ch_a = *(oneg->line[i].lines_ptr);
    char ch_b = *(oneg->line[j].lines_ptr);

    while (ch_a != '\n' || ch_b)
    {
        ch_a = *(oneg->line[i].lines_ptr + k);
        ch_b = *(oneg->line[j].lines_ptr + k);
        if (ch_a > ch_b)
            return 1;
        if (ch_b > ch_a)
            return -1;
    }

    return 0;
}

//----------------------------------------------------------------------//

void Swapper (struct Onegin * oneg, int i, int j)
{
    char temp = *(oneg->line->lines_ptr + i);
    *(oneg->line->lines_ptr + i) = *(oneg->line->lines_ptr + j);
    *(oneg->line->lines_ptr + j) = temp;
}

//----------------------------------------------------------------------//

void FileOutput (struct Onegin * oneg)
{
    assert (oneg != NULL);

    for (size_t i = 0; i <= oneg->lines_amount; i++)
    {
        for (int j = 0; j <= oneg->line->line_len; i++)
        {
            char output = *(oneg->line->lines_ptr + oneg->line->line_len + j);
            printf ("%c", output);
        }
    }
}

//----------------------------------------------------------------------//

/*void FileWriter (struct Onegin * oneg)
{
    assert (oneg != NULL);

    char * buffer_sorted = (char *) calloc (oneg.file_size + 1, sizeof(char));

    for (int i = 0; i < oneg.file_size + 1, i++)
    {

    }

    output_file = fopen ("output.txt", "r");
    size_t ReadStatus = fwrite (buffer_sorted, sizeof(char), oneg.file_size, output_file);
    assert (ReadStatus != oneg.file_size);

    fclose (oneg.FILE_NAME);
    free (buffer_sorted);
}*/

//----------------------------------------------------------------------//

size_t GimmeFileSize (struct Onegin * oneg)
{
    struct stat st = {};
    fstat (fileno(oneg->file_onegin), &st);
    assert (oneg->file_size != 0);

    return st.st_size;
}

//----------------------------------------------------------------------//

size_t BufferLinesCounter (struct Onegin * oneg)
{
    size_t lines = 0;

    for (size_t i = 0; i != oneg->file_size + 1; i++)
    {
        if (*(oneg->buffer + i) == '\r')
        {
            *(oneg->buffer + i) = '\0';
            lines++;
        }
    }

    return lines;
}

//----------------------------------------------------------------------//
