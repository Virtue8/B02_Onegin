
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

size_t BufferLinesCounter (struct Onegin * oneg);
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
    printf("reader execution is successful\n");
    LineSeparator (&oneg);
    printf("separator execution is successful\n");
    FileOutput (&oneg);
    printf("writer execution is successful (normal)\n");    
    Sorter (&oneg);
    printf("sorter execution is successful\n");
    FileOutput (&oneg);
    printf("writer execution is successful (sorted)\n");
    ReversedSorter (&oneg);
    printf ("reversed sorter execution is successful\n");
    FileOutput (&oneg);
    printf("writer execution is successful (reverse sorted)\n");

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

    oneg->lines_amount = BufferLinesCounter (oneg);                                                // counts the amount of lines in the buffer
    printf ("%lu\n", oneg->lines_amount);

    oneg->line = (Line*) calloc (oneg->lines_amount, sizeof(Line));
    assert (oneg->line != NULL);                                                                   // line counter (local)
    size_t prev_i_value = 0;

    for (size_t i = 0; i != oneg->file_size; i++)
    {
        if (*(oneg->buffer + i) == '\0')
        {
            oneg->line[i].line_len = i - prev_i_value;
            printf ("%ld %p\n", oneg->line[i].line_len, &oneg->line[i].line_len);
            oneg->line[i].lines_ptr = oneg->buffer + i - oneg->line[i].line_len;
            printf ("%p\n i = %ld\n", oneg->line[i].lines_ptr, i);


            prev_i_value = i;
        }
    }
}

//----------------------------------------------------------------------//

void Sorter (struct Onegin * oneg)
{
    assert (oneg != NULL);
    
    for (size_t i = 0; i < oneg->lines_amount; i++)
    {
        for (size_t j = 1; j < oneg->line->line_len - i; j++)
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
    
    for (int i = 0; i < (int) oneg->lines_amount; i++)
    {
        for (size_t j = 1; j < oneg->line->line_len - i; j++)
        {
            if (Comparator(i, j, oneg) == 1)
                Swapper(oneg, i, j);
        }
    }
}

//----------------------------------------------------------------------//

int Comparator (size_t i, size_t j, struct Onegin * oneg)
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

void Swapper (struct Onegin * oneg, size_t i, size_t j)
{
    char * temp = oneg->line[j].lines_ptr;
    oneg->line[j].lines_ptr = oneg->line[i].lines_ptr;
    oneg->line[i].lines_ptr = temp;
}

//----------------------------------------------------------------------//

void FileOutput (struct Onegin * oneg)
{
    assert (oneg != NULL);
    printf("cfkoemkcds;a");
    for (size_t i = 0; i < oneg->lines_amount; i++)
    {
        printf("%s\n", oneg->line[i].lines_ptr);
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

size_t BufferLinesCounter (struct Onegin * oneg)
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
