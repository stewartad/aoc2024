#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int compare(const void *l, const void *r)
{
    return *(long *)l < *(long *)r;
}

int read_nums(char *line, long *l, long *r)
{
    char *p, *q;
    *l = strtol(line, &p, 10);
    if (*p == '\0')
    {
        return 1;
    }
    *r = strtol(p, &q, 10);
    return 0;
}

int main(int argc, char const *argv[])
{
    char* filename;
    FILE *fd;
    char buf[1024];
    char *line;
    size_t count;
    long l, r;
    long list_l[10000];
    long list_r[10000];
    long list_count[100000] = {0};
    long total;

    if (argc < 2) {
        filename = "input";
    } else
    {
        filename = argv[1];
    }

    fd = fopen(filename, "r");
    if (fd == NULL)
        return 1;
    count = 0;    
    while(1) {
        line = fgets(buf, 1024, fd);
        if (!line)
            break;
        int rc = read_nums(line, &l, &r);
        list_l[count] = l;
        list_r[count] = r;
        count++;
    }

    qsort(list_l, count, sizeof(long), &compare);
    qsort(list_r, count, sizeof(long), &compare);

    total = 0;
    for (int i = 0; i < count; i++)
    {
        long b = list_r[i];
        list_count[b] += 1;
    }
    for (int i = 0; i < count; i++)
    {
        long a = list_l[i];
        total += a * list_count[a];
    }
    printf("total %ld\n", total);
    return 0;
}
