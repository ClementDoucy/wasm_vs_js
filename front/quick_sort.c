#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
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

    if (!arr)
        return 0;
    for (; *arr; arr++) len++;
    return len;
}

static void destroy_double_arr(void **arr)
{
    if (!arr)
        return;
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
static void *get_numbers_error(char **splited, int *nbrs_arr)
{
    destroy_double_arr((void **)splited);
    if (nbrs_arr)
        free(nbrs_arr);
    return NULL;
}

static bool is_number(char *str)
{
    if (!str)
        return false;
    if (*str == '-' && !(*(++str)))
        return false;
    for (; *str; str++)
        if (*str < '0' || *str > '9')
            return false;
    return true;
}

static int *get_numbers(char *nbrs_as_str, size_t *len)
{
    char **splited = str_split(nbrs_as_str, ' ');
    int *nbrs_arr = NULL;

    if (!splited)
        return NULL;
    *len = double_arr_len((void **)splited);
    if (!(nbrs_arr = malloc(sizeof(int) * (*len))))
        return get_numbers_error(splited, NULL);
    for (size_t i = 0; i < *len; i++) {
        if (!is_number(splited[i])) {
            return get_numbers_error(splited, nbrs_arr);
        }
        nbrs_arr[i] = atoi(splited[i]);
    }
    destroy_double_arr((void **)splited);
    return nbrs_arr;
}

static void swap(int *a, int *b)
{
    int save = *a;

    *a = *b;
    *b = save;
}

static size_t partition(int *nbrs_arr, int first_idx, int last_idx)
{
    size_t next_pivot_idx = first_idx;
    int pivot = nbrs_arr[last_idx];

    for (int i = first_idx; i < last_idx; i++)
        if (nbrs_arr[i] <= pivot) {
            swap(&(nbrs_arr[i]), &(nbrs_arr[next_pivot_idx]));
            next_pivot_idx++;
        }
    swap(&(nbrs_arr[last_idx]), &(nbrs_arr[next_pivot_idx]));
    return next_pivot_idx;
}

static void quick_sort(int *nbrs_arr, int first_idx, int last_idx)
{
    size_t pivot_idx = 0;

    if (first_idx >= last_idx)
        return;
    pivot_idx = partition(nbrs_arr, first_idx, last_idx);
    quick_sort(nbrs_arr, first_idx, pivot_idx - 1);
    quick_sort(nbrs_arr, pivot_idx + 1, last_idx);
}

int *launch_sort(char *nbrs_as_str)
{
    char *cleaned = str_clean(nbrs_as_str);
    int *nbrs_arr = NULL;
    char *sorted = NULL;
    size_t len = 0;

    if (!cleaned || !strlen(cleaned))
        return str_clean_error(cleaned);
    nbrs_arr = get_numbers(cleaned, &len);
    free(cleaned);
    if (!nbrs_arr)
        return NULL;
    quick_sort(nbrs_arr, 0, (int)len - 1);
    return nbrs_arr;
}