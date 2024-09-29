
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
int BubbleSort (char * a, size_t len_a, char * b, size_t len_b);
void Swapper (struct Onegin * oneg, int i, int j);
//void FileWriter (struct Onegin * oneg);
void FileOutput (struct Onegin * oneg);

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
    printf("reader\n");
    LineSeparator (&oneg);
    printf("separator\n");
    Sorter (&oneg);
    printf("sorter\n");
    FileOutput (&oneg);
    printf("writer\n");

    free (oneg.buffer);
    free (oneg.line->lines_ptr);
    free (&oneg.line->line_len);
}

//--------------------------- Other functions --------------------------//

void FileReader (struct Onegin * oneg)
{
    assert (oneg != NULL);

    oneg->file_onegin = fopen (oneg->file_name, "rb");
    assert (oneg->file_onegin != NULL);                 // source file opening

    struct stat st = {};                               // getting the file size
    fstat (fileno(oneg->file_onegin), &st);             // through fstat()
    oneg->file_size = st.st_size;
    assert (oneg->file_size != 0);

    oneg->buffer = (char *) calloc ((oneg->file_size + 1), sizeof(char));       // reading the content
    assert (oneg->buffer != NULL);                                                  // to buffer

    size_t ReadStatus = fread (oneg->buffer, sizeof(char), oneg->file_size, oneg->file_onegin);
    if (ReadStatus != oneg->file_size)
        printf ("wrong reading\n");

    fclose (oneg->file_onegin);
}

//----------------------------------------------------------------------//

void LineSeparator (struct Onegin * oneg)
{
    assert (oneg != NULL);

    oneg->lines_amount = 1;
    *(oneg->buffer + oneg->file_size + 1) = '\0';

    for (size_t i = 0; i != oneg->file_size + 1; i++)         // first buffer passage
    {                                                     // getting the lines number
        if (*(oneg->buffer + i) == '\r')
        {
            *(oneg->buffer + i) = '\0';
            oneg->lines_amount++;
        }
    }

    printf ("%d", oneg->lines_amount);

    oneg->line->lines_ptr = (char *) calloc (oneg->lines_amount + 1, sizeof(size_t));
    printf ("hui\n");
    oneg->line->line_len = (size_t) calloc (oneg->lines_amount + 1, sizeof(size_t));
    assert (oneg->line->lines_ptr != NULL);
    assert (oneg->line->line_len != 0);

    int curr_line_num = 0;                                // line counter (local)
    int prev_i_value = -1;
    int len = 0;

    for (size_t i = 0; i != oneg->file_size + 1; i++)         // second buffer passage
    {                                                     // to get lines data
        if (*(oneg->buffer + i) == '\n')
        {
            len = i - prev_i_value - 2;
            oneg->line->line_len = len + curr_line_num;                            // entering line length in len data buffer (without \0 at the end)
            oneg->line->lines_ptr = oneg->buffer + i - len - 1 + curr_line_num;     // entering line pointer in ptr data buffer

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

    for (int i = 0; i < oneg->line->line_len; i++)
    {
        len_a = oneg->line->line_len + i;
        a = oneg->line->lines_ptr + i;

        for (int j = 1; j < oneg->line->line_len - i; j++)
        {
            len_b = oneg->line->line_len + j;
            b = oneg->line->lines_ptr + j;

            if (BubbleSort(a, len_a, b, len_b) == 1)
                Swapper(oneg, i, j);
        }
    }
}

//----------------------------------------------------------------------//

int BubbleSort (char * a, size_t len_a, char * b, size_t len_b)
{
    for (size_t k = 0; k < max(len_a, len_b); k++)
    {
        char ch_a = *(a + k);
        char ch_b = *(b + k);

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
