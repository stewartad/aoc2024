
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DEBUG 0

int check_horizontal(char arr[200][200], size_t len, int i, int j)
{
    int result = 0;
    char *row = arr[i];

    // check right
    if (j + 3 < len)
    {
        if (row[j + 1] == 'M' && row[j + 2] == 'A' && row[j + 3] == 'S')
        {
            result++;
        }
    }
    // check left
    if (j - 3 >= 0)
    {
        if (row[j - 1] == 'M' && row[j - 2] == 'A' && row[j - 3] == 'S')
        {
            result++;
        }
    }
    return result;
}

int check_vertical(char arr[200][200], size_t len, size_t count, int i, int j)
{
    int result = 0;
    // check down
    if (i + 3 < count)
    {
        if (arr[i + 1][j] == 'M' && arr[i + 2][j] =='A' && arr[i + 3][j] == 'S')
        {
            result++;
        }
    }
    // check up
    if (i - 3 >= 0)
    {
        if (arr[i - 1][j] == 'M' && arr[i - 2][j] == 'A' && arr[i - 3][j] == 'S')
        {
            result++;
        }
    }
    return result;
}

int check_diagonal(char arr[200][200], size_t len, size_t count, int i, int j)
{
    int result = 0;
    // check up-right
    if (i - 3 >= 0 && j + 3 < len)
    {
        if (arr[i - 1][j + 1] == 'M' && arr[i -2][j + 2] == 'A' && arr[i - 3][j + 3] == 'S')
        {
            result++;
        }
    }
    // check up-left
    if (i - 3 >= 0 && j - 3 >= 0)
    {
        if (arr[i - 1][j - 1] == 'M' && arr[i -2][j - 2] == 'A' && arr[i - 3][j - 3] == 'S')
        {
            result++;
        }
    }
    // check down-right
    if (i + 3 < count && j + 3 < len)
    {
        if (arr[i + 1][j + 1] == 'M' && arr[i + 2][j + 2] == 'A' && arr[i + 3][j + 3] == 'S')
        {
            result++;
        }
    }
    // check down-left
    if (i + 3 < count && j - 3 >= 0)
    {
        if (arr[i + 1][j - 1] == 'M' && arr[i + 2][j - 2] == 'A' && arr[i + 3][j - 3] == 'S')
        {
            result++;
        }
    }
    return result;
}

int process_puzzle(char arr[200][200], size_t count, size_t length)
{
    int result = 0;
    int h, v, d;
    h = 0;
    v = 0;
    d = 0;
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < length; j++)
        {
            if (arr[i][j] == 'X')
            {
                h += check_horizontal(arr, length, i, j);
                v += check_vertical(arr, length, count, i, j);
                d += check_diagonal(arr, length, count, i, j);
            }
        }
    }
    if (DEBUG)
    {
        printf("horizontal: %d, vertical %d, diagonal %d\n", h, v, d);
    }
    result = h + v + d;
    return result;
}

int main(int argc, char const *argv[])
{
    char* filename;
    FILE *fd;
    char buf[1024];
    char *line;
    size_t count;
    size_t length;
    char puzzle[200][200];
    int result;

    if (argc < 2) {
        filename = "example";
    } else
    {
        filename = argv[1];
    }

    fd = fopen(filename, "r");
    if (fd == NULL)
        return 1;
    count = 0;    
    while(1) {
        line = fgets(puzzle[count], 1024, fd);
        if (!line)
            break;
        count++;
    }
    char *p = puzzle[0];
    length = 0;
    while (*p != '\0' && *p != '\n')
    {
        p++;
        length++;
    }

    if (DEBUG)
    {
        printf("count: %d, length: %d\n", count, length);
        for (int i = 0; i < count; i++)
        {
            printf("%s", puzzle[i]);
        }
        printf("\n");
    }

    result = process_puzzle(puzzle, count, length);
    printf("total %d\n", result);
    return 0;
}
