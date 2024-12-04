
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DEBUG 0

int check_diagonal(char arr[200][200], size_t len, size_t count, int i, int j)
{
    int result = 0;

    if (i == 0 || j == 0 || i == count - 1 || j == len - 1)
        return result;

    if (((arr[i - 1][j - 1] == 'M' && arr[i + 1][j + 1] == 'S') || (arr[i - 1][j - 1] == 'S' && arr[i + 1][j + 1] == 'M')) 
        && ((arr[i - 1][j + 1] == 'M' && arr[i + 1][j - 1] =='S') || (arr[i - 1][j + 1] == 'S' && arr[i + 1][j - 1] == 'M')))
        result++;

    return result;
}

int process_puzzle(char arr[200][200], size_t count, size_t length)
{
    int result = 0;
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < length; j++)
        {
            if (arr[i][j] == 'A')
            {
                result += check_diagonal(arr, length, count, i, j);
            }
        }
    }
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
