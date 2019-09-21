#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//TOOLS//
static char *str_clean(char *str)
{
    char *new = NULL;
    int i = 0;
    int k = 0;

    if (!str || !(new = malloc(sizeof(char) * (strlen(str) + 1))))
        return NULL;
    for (; str[i] == ' ' || str[i] == '\t'; i++);
    for (; str[i]; i++) {
        if (str[i] != ' ' && str[i] != '\t')
            new[k++] = str[i];
        if (str[i + 1] && (str[i] == ' ' || str[i] == '\t')
            && str[i + 1] != ' ' && str[i + 1] != '\t')
            new[k++] = ' ';
    }
    new[k] = '\0';
    return new;
}

static size_t split_len(const char *str, char c)
{
    size_t size = 0;
    int i = 0;

    for (; str[i] == c; i++);
    if (!str[i])
        return 0;
    size = 1;
    for (; str[i]; i++)
        if (str[i + 1] && str[i] == c && str[i + 1] != c)
            size++;
    return size;
}

static char *dup_until_delim(const char *str, char c)
{
    size_t size = 0;
    char *new = NULL;

    for (; str[size] && str[size] != c; size++);
    if (!(new = malloc(sizeof(char) * (size + 1))))
        return NULL;
    for (int i = 0; i < (int)size; i++)
        new[i] = str[i];
    new[size] = '\0';
    return new;
}

static char **str_split(const char *str, char c)
{
    int i = 0;
    int k = 0;
    size_t size = 0;
    char **arr = NULL;

    if (!str || !(size = split_len(str, c)) ||
        !(arr = malloc(sizeof(char *) * (size + 1))))
        return NULL;
    for (; str[i] == c; i++);
    for (; str[i]; i++)
        if (!i || (str[i] && str[i] != c && str[i - 1] == c)) {
            arr[k] = dup_until_delim(&str[i], c);
            k++;
        }
    arr[k] = NULL;
    return arr;
}

static size_t double_arr_len(void **arr)
{
    size_t len = 0;

    while (*(arr++)) len++;
    return len;
}

static void destroy_double_arr(void **arr)
{
    for (int i = 0; arr[i]; i++)
        free(arr[i]);
    free(arr);
}
//ERROR FUNCTION//
static void *str_clean_error(char *str)
{
    if (str)
        free(str);
    return NULL;
}
//MAIN FUNCTIONS//
char *launch_sort(char *nbrs_as_str)
{
    char *cleaned = str_clean(nbrs_as_str);
    int *nbrs_arr = NULL;
    char **splited = NULL;
    size_t len = 0;

    if (!cleaned || !strlen(cleaned))
        return str_clean_error(cleaned);
    dprintf(1, "cleaned = [%s]\n", cleaned);
    splited = str_split(cleaned, ' ');
    free(cleaned);
    if (!splited)
        return NULL;
    len = double_arr_len((void **)splited);
    // if (!(nbrs_arr = get_numbers(splited)))
    //     return NULL;
    dprintf(1, "len = [%ld]\n", len);
    for (int i = 0; splited[i]; i++)
        dprintf(1, "%s\n", splited[i]);
    destroy_double_arr((void **)splited);
    return NULL;
}

int main(void)
{
    char *sorted = launch_sort("                1  ddzadzadza                   2                          3                              4                           5                       ");
    // dprintf(1, "[%s]\n", sorted);
    return 0;
}