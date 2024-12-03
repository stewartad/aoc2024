#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

// read numbers from buf into arr, return amount of numbers read
int read_nums(char *buf, long *arr, size_t arr_size)
{
    char *start, *end;
    int count;

    count = 0;
    start = buf;
    for (int i = 0; i < arr_size; i++)
    {
        long x = strtol(start, &end, 10);
        if (x == 0)
            break;
        arr[i] = x;
        start = end;
        count++;
    }
    return count;
}

int check_is_bad(int direction, int a, int b)
{
    int bad = 0;
    if (direction > 0)
    {
        if (a > b)
            bad++;
        if (b - a > 3 || b - a < 1)
            bad++;
    }
    if (direction < 0)
    {
        if (a < b)
            bad++;
        if (a - b > 3 || a - b < 1)
            bad++;
    }
    return bad;
}

int main(int argc, char const *argv[])
{
    const char* filename;
    FILE *fd;
    char buf[1024];
    char *line;
    size_t count;
    long l, r;
    long list[1024][32];
    long list_sizes[1024];
    long result;

    printf("Advent of Code 2024\n");
    printf("Day 2 - Part 1\n");

    if (argc < 2) {
        filename = "input";
    } else
    {
        filename = argv[1];
    }

    fd = fopen(filename, "r");
    if (fd == NULL)
    {
        printf("Could not open file");
        return 1;
    }
    
    count = 0;
    while(1) {
        line = fgets(buf, 1024, fd);
        if (line == NULL)
            break;
        list_sizes[count] = read_nums(line, list[count], 32);
        count++;
    }

    result = 0;
    for (int i = 0; i < count; i++)
    {
        int direction = 1; // +1 for increasing, -1 for decreasing
        long x = list[i][0];
        long y = list[i][1];
        if (x < y)
            direction = 1;
        else if (x > y)
            direction = -1;
        else
            continue;
        int bad = 0;
        for (int j = 0; j < list_sizes[i]; j++)
        {
            if (j == list_sizes[i] - 1)
                break;
            long a = list[i][j];
            if (DEBUG)
            {
                printf("%ld\t", a);
            }
            long b = list[i][j + 1];
            bad += check_is_bad(direction, a, b);
        }
        if (!bad)
            result++;
        if (DEBUG)
            bad ? printf("UNSAFE\n") : printf("SAFE\n");
    }

    printf("%d\n", result);
    return 0;
}
