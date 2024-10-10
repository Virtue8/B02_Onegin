
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
void FileOutput (struct Onegin * oneg);

void Sorter (struct Onegin * oneg, int (*f)(size_t, size_t, struct Onegin *));
int Comparator (size_t i, size_t j, struct Onegin * oneg);
int RevComparator (size_t i, size_t j, struct Onegin * oneg);
void Swapper (struct Onegin * oneg, size_t i, size_t j);

//------------------------ Secondary Functions --------------------------//

void IgnorePunctuationRule (char ch_a, char ch_b);
size_t BufferLinesRefactorer (struct Onegin * oneg);
void GimmeFileSize (struct Onegin * oneg);
void NormalFileOutput (struct Onegin * oneg);

//----------------------- Constants and Structs -------------------------//

enum Mode
{
    NORMAL,
    REVERSED
};

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
    Sorter (&oneg, Comparator);
    FileOutput (&oneg);
    printf("\nNormal Sorted Text\n\n");
    Sorter (&oneg, RevComparator);
    FileOutput (&oneg);
    printf("Reverse Sorted Text\n\n");
    NormalFileOutput (&oneg);
    printf("\nOriginal Text\n\n");

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

void Sorter (struct Onegin * oneg, int (*f)(size_t, size_t, struct Onegin *))
{
    assert (oneg != NULL);
    for (size_t i = 0; i < oneg->lines_amount; i++)
    {
        for (size_t j = i + 1; j < oneg->lines_amount; j++)
        {
            if ((*f)(i, j, oneg) == 1)
                Swapper(oneg, i, j);
        }
    }
}

//----------------------------------------------------------------------//

int Comparator (size_t i, size_t j, struct Onegin * oneg)
{
    int k = 1;
    char ch_a = *(oneg->line[i].lines_ptr + 1);
    char ch_b = *(oneg->line[j].lines_ptr + 1);

    while (ch_a != '\0' && ch_b != '\0')
    {
        ch_a = *(oneg->line[i].lines_ptr + k);
        
        while (ch_a == '!' || ch_a == ',' || ch_a == '.' || ch_a == ':')
            ch_a = *(&ch_a + 1);

        ch_b = *(oneg->line[j].lines_ptr + k);
        
        while (ch_b == '!' || ch_b == ',' || ch_b == '.' || ch_b == ':')
            ch_b = *(&ch_b + 1);
        
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

int RevComparator (size_t i, size_t j, struct Onegin * oneg)
{
    int k = 1;
    char ch_a = *(oneg->line[i].lines_ptr + oneg->line[i].line_len - k);
    char ch_b = *(oneg->line[j].lines_ptr + oneg->line[j].line_len - k);

    while (ch_a != '\0' && ch_b != '\0')
    {
        ch_a = *(oneg->line[i].lines_ptr + oneg->line[i].line_len - k);
        ch_b = *(oneg->line[j].lines_ptr + oneg->line[j].line_len - k);

        if (ch_a == '!' || ch_a == ',' || ch_a == '.' || ch_a == ':' || ch_a == ';' || ch_a == ' ')
            ch_a = *(oneg->line[i].lines_ptr + oneg->line[i].line_len - k - 1);

        if (ch_b == '!' || ch_b == ',' || ch_b == '.' || ch_b == ':' || ch_b == ';' || ch_b == ' ')
            ch_b = *(oneg->line[j].lines_ptr + oneg->line[j].line_len - k - 1);

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
    printf ("\n");
}

//----------------------------------------------------------------------//

void NormalFileOutput (struct Onegin * oneg)
{
    assert (oneg != NULL);
    for (size_t i = 0; i < oneg->file_size; i++)
    {
        if (oneg->buffer[i] != '\0')
            printf ("%c", oneg->buffer[i]);
        else
            printf ("\n");
    }
}

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

void IgnorePunctuationRule (char ch_a, char ch_b)
{
    if (ch_a == '!' || ch_a == ',' || ch_a == '.' || ch_a == ':' || ch_a == ';' || ch_a == ' ')
        ch_a = *(&ch_a - 1);

    if (ch_b == '!' || ch_b == ',' || ch_b == '.' || ch_b == ':' || ch_b == ';' || ch_b == ' ')
        ch_b = *(&ch_b - 1);
}

//----------------------------------------------------------------------//