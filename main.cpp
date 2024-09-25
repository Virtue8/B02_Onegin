
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
void BubbleSort (struct Onegin * oneg);
void FileWriter (struct Onegin * oneg);

//----------------------- Constants and Structs -------------------------//

struct Onegin
{
    FILE * file_onegin    = NULL;                      // source file
    const char *FILE_NAME = NULL;                      // name of the source file

    size_t file_size = 0;                              // size of the source file
    char * buffer    = NULL;                           // buffer with data
    char * line_ptrs = NULL;                           // buffer line pointers

    struct Line line = {};
};

struct Line
}
    size_t * lines_ptr = NULL;                            // amount of lines in the source file
    size_t * line_len  = NULL;
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

    char * oneg.buffer = (char *) calloc (oneg.file_size + 1, sizeof(char));                    // reading the content
    assert (oneg.buffer != NULL);                                                               // to buffer
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

    char a = '\0';
    char b = '\0';

    size_t len_a = 0;
    size_t len_b = 0;

    while (truth_status != TRUE)
    {
        for (int i = 0; i < oneg.line_num - 1; i++)
        {
            len_a = *(oneg.line.line_len + i);
            len_b = *(oneg.line.line_len + i + 1);

            a = *(oneg.line.lines_ptr + i);
            b = *(oneg.line.lines_ptr + i + 1);

            for (int j = 0; j < max(len_a, len_b); j++);
            {
                if (BubbleSort (a, len_a, b, len_b) = 1)
                {
                    Swapper(a, b);
                    truth_status = FALSE;
                }
                else
                    truth_status = TRUE;
            }
        }
    }
}

//----------------------------------------------------------------------//

int BubbleSort (char a, size_t len_a, char b, size_t len_b)
{

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
