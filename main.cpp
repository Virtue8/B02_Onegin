
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
void ReversedSorter (struct Onegin * oneg);
int Comparator (size_t i, size_t j, struct Onegin * oneg);
void Swapper (struct Onegin * oneg, size_t i, size_t j);
//void FileWriter (struct Onegin * oneg);
void FileOutput (struct Onegin * oneg);

//------------------------ Secondary Functions --------------------------//

size_t BufferLinesRefactorer (struct Onegin * oneg);
void GimmeFileSize (struct Onegin * oneg);

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
    size_t line_len  = 0;
};

//-------------------------------- main ---------------------------------//

int main ()
{
    Onegin oneg = {};
    oneg.file_name = "text.txt";

    FileReader (&oneg);
    LineSeparator (&oneg);
    FileOutput (&oneg);
    printf("\nNormal Text\n\n");    
    Sorter (&oneg);
    FileOutput (&oneg);
    printf("\nNormal Sorted Text\n\n");
    //ReversedSorter (&oneg);
    //FileOutput (&oneg);
    //printf("Reverse Sorted Text\n");

    free (oneg.buffer);
    free (oneg.line);
}

//--------------------------- Other functions --------------------------//

void FileReader (struct Onegin * oneg)
{
    assert (oneg != NULL);

    oneg->file_onegin = fopen (oneg->file_name, "rb");                                             // source file opening
    assert (oneg->file_onegin != NULL);

    GimmeFileSize (oneg);
    assert (oneg->file_size != 0);

    oneg->buffer = (char *) calloc ((oneg->file_size + 1), sizeof(char));
    assert (oneg->buffer != NULL);                                                                 

    size_t ReadStatus = fread (oneg->buffer, sizeof(char), oneg->file_size, oneg->file_onegin);
    if (ReadStatus != oneg->file_size)
        printf ("wrong reading\n");

    *(oneg->buffer + oneg->file_size) = '\0';

    fclose (oneg->file_onegin);
}

//----------------------------------------------------------------------//

void LineSeparator (struct Onegin * oneg)
{
    assert (oneg != NULL);

    oneg->lines_amount = BufferLinesRefactorer (oneg);                                             // counts the amount of lines in the buffer

    oneg->line = (Line*) calloc (oneg->lines_amount, sizeof(Line));
    assert (oneg->line != NULL);                                                                   // line counter (local)
    size_t prev_i_value = 0;
    int k = 0;

    for (size_t i = 0; i < oneg->file_size+1; i++)
    {
        if (oneg->buffer[i] == '\0')
        {
            oneg->line[k].line_len = i - prev_i_value;
            oneg->line[k].lines_ptr = oneg->buffer + i - oneg->line[k].line_len;
            prev_i_value = i;
            assert (oneg->line[k].lines_ptr);
            k += 1;
        }
    }
    assert (oneg->line[0].lines_ptr);
}

//----------------------------------------------------------------------//

void Sorter (struct Onegin * oneg)
{
    assert (oneg != NULL);
    for (size_t i = 0; i < oneg->lines_amount; i++)
    {
        for (size_t j = i + 1; j < oneg->lines_amount; j++)
        {
            if (Comparator(i, j, oneg) == 1)
                Swapper(oneg, i, j);
        }
    }
}

//----------------------------------------------------------------------//

void ReversedSorter (struct Onegin * oneg)
{
    assert (oneg != NULL);
    for (size_t i = 0; i < oneg->lines_amount; i++)
    {
        for (size_t j = i + 1; j < oneg->lines_amount; j++)
        {
            int c = Comparator(i, j, oneg);
            printf ("\n%d\n", c);
            if (c == -1)
                Swapper(oneg, i, j);
        }
    }
}

//----------------------------------------------------------------------//

int Comparator (size_t i, size_t j, struct Onegin * oneg)
{
    int k = 0;
    char ch_a = *(oneg->line[i].lines_ptr + 1);
    char ch_b = *(oneg->line[j].lines_ptr + 1);

    while (ch_a != '\0' && ch_b != '\0')
    {
        ch_a = *(oneg->line[i].lines_ptr + k);
        ch_b = *(oneg->line[j].lines_ptr + k);
        if (ch_a > ch_b)
            return 1;
        if (ch_b > ch_a)
            return -1;
        else
            k += 1;
    }

    return 0;
}

//----------------------------------------------------------------------//

void Swapper (struct Onegin * oneg, size_t i, size_t j)
{
    struct Line temp = oneg->line[j];
    oneg->line[j] = oneg->line[i];
    oneg->line[i] = temp;
}

//----------------------------------------------------------------------//

void FileOutput (struct Onegin * oneg)
{
    assert (oneg != NULL);
    for (size_t i = 0; i < oneg->lines_amount; i++)
    {
        assert (oneg->line[i].lines_ptr);
        for (size_t j = 0; j < oneg->line[i].line_len; j++)
            printf ("%c", *(oneg->line[i].lines_ptr + j));
        printf ("\n");
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

void GimmeFileSize (struct Onegin * oneg)
{
    struct stat st = {};
    fstat (fileno(oneg->file_onegin), &st);
    oneg->file_size = (size_t) st.st_size;
}

//----------------------------------------------------------------------//

size_t BufferLinesRefactorer (struct Onegin * oneg)
{
    size_t lines = 0;

    for (size_t i = 0; i != oneg->file_size + 1; i++)
    {
        if (*(oneg->buffer + i) == '\n')
        {
            *(oneg->buffer + i) = '\0';
            lines++;
        }
    }

    return lines + 1;
}

//----------------------------------------------------------------------//
