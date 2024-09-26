
//------------------------ Libraries and Files --------------------------//

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <TXLib.h>
#include <stdlib.h>
#include <sys/stat.h>

const char * FILE_NAME = "";

//------------------------ Main Functions Init --------------------------//

void FileReader (struct Onegin * oneg);
void LineSeparator (struct Onegin * oneg);
void Sorter (struct Onegin * oneg);
int BubbleSort (char a, size_t len_a, char b, size_t len_b, struct Onegin * oneg);
void FileWriter (struct Onegin * oneg);

//----------------------- Constants and Structs -------------------------//

struct Onegin
{
    FILE * file_onegin    = NULL;                      // source file
    const char *file_name = NULL;                      // name of the source file

    size_t file_size = 0;                              // size of the source file
    char * buffer    = NULL;                           // buffer with data
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
    assert (oneg != NULL);

    Onegin oneg = {};
    oneg.file_name = "text.txt";

    FileReader (&oneg);
    LineSeparator (&oneg);
    Sorter (&oneg);
    FileWriter (&oneg);

    free (oneg.buffer);
    free (oneg.line.lines_ptr);
    free (oneg.line.line_len);
}

//--------------------------- Other functions --------------------------//

void FileReader (struct Onegin * oneg)
{
    assert (oneg != NULL);                             // checking the right memory allocation
    assert (oneg.buffer != NULL);

    oneg.file_onegin = fopen (oneg.file_name, "rb");
    assert (oneg.file_onegin != NULL);                 // source file opening

    struct stat st = {};                               // getting the file size
    fstat (fileno(oneg.file_onegin), &st);             // through fstat()
    oneg.file_size = st.st_size;
    assert (oneg.file_size != 0);

    char * oneg.buffer = (char *) calloc (oneg.file_size + 1, sizeof(char));                    // reading the content
    assert (oneg.buffer != NULL);
                                                                   // to buffer
    size_t ReadStatus = fread (oneg.buffer, sizeof(char), oneg.file_size, oneg.file_onegin);
    assert (ReadStatus != ferror);

    fclose (oneg.file_onegin);
}

//----------------------------------------------------------------------//

void LineSeparator (struct Onegin * oneg)
{
    assert (oneg != NULL);

    oneg.lines_amount = 1;
    *(oneg.buffer + oneg.file_size + 1) = '\0';

    for (int i = 0; i != oneg.file_size + 1; i++)         // first buffer passage
    {                                                     // getting the lines number
        if (*(oneg.buffer + i) == '\r')
        {
            *(oneg.buffer + i) = '\0';
            oneg.lines_amount++;
        }
    }

    size_t * oneg.line.lines_ptr = (size_t *) calloc (oneg.lines_amount, sizeof(size_t));
    size_t * oneg.line.line_len = (size_t *) calloc (oneg.lines_amount, sizeof(size_t));

    int curr_line_num = 0;                                // line counter (local)
    int prev_i_value = -1;
    int len = 0;

    for (int i = 0; i != oneg.file_size + 1; i++)         // second buffer passage
    {                                                     // to get lines data
        if (*(oneg.buffer + i) == '\n')
        {
            len = i - prev_i_value - 2;
            *(oneg.lines.line_len + curr_line_num) = len;                            // entering line length in len data buffer (without \0 at the end)
            *(oneg.lines.lines_ptr + curr_line_num) = oneg.buffer + i - len - 1;     // entering line pointer in ptr data buffer

            prev_i_value = i;
        }
    }
}

//----------------------------------------------------------------------//

void Sorter (struct Onegin * oneg)
{
    assert (oneg != NULL);

    int truth_status = FALSE;

    char * a = NULL;
    char * b = NULL;

    size_t len_a = 0;
    size_t len_b = 0;

    while (truth_status != TRUE)
    {
        for (int i = 0; i < oneg.line_num - 1; i++)
        {
            len_a = *(oneg.line.line_len + i);
            len_b = *(oneg.line.line_len + i + 1);

            a = oneg.line.lines_ptr + i;
            b = oneg.line.lines_ptr + i + 1;

            if (BubbleSort (a, len_a, b, len_b, &oneg) = 1)
            {
                Swapper(&oneg, i);
                truth_status = FALSE;
            }
            else
                truth_status = TRUE;
        }
    }
}

//----------------------------------------------------------------------//

int BubbleSort (char * a, size_t len_a, char * b, size_t len_b, struct Onegin * oneg) //
{
    for (int j = 0; j < max(len_a, len_b); j++);
    {
        char ch_a = *(a + j);
        char ch_b = *(b + j);

        if (ch_a > ch_b)
        {
            return 1;
        }
        if (ch_b > ch_a)
            return -1;
    }
}

//----------------------------------------------------------------------//

void Swapper (struct Onegin * oneg, int i)
{
    size_t temp = *(oneg.line.lines_ptr + i);
    *(oneg.line.lines_ptr + i) = *(oneg.line.lines_ptr + i + 1);
    *(oneg.line.lines_ptr + i + 1) = temp;
}

//----------------------------------------------------------------------//

void FileWriter (struct Onegin * oneg)
{
    assert (oneg != NULL);

    char * buffer_sorted = (char *) calloc (oneg.file_size + 1, sizeof(char));

    for (int i = 0; i < oneg.file_size + 1, i++)
    {
        *(buffer_sorted + i) = ...;
    }

    output_file = fopen ("output.txt", "r");
    size_t ReadStatus = fwrite (buffer_sorted, sizeof(char), oneg.file_size, output_file);
    assert (ReadStatus != oneg.file_size);

    fclose (oneg.FILE_NAME);
    free (buffer_sorted);
}
