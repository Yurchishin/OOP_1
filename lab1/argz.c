/**********************************************************************************************

*file: argz.c

*related files: none

*author: Rybak Yura

*written: 04/10/2018

*last modified: 09/10/2018

**********************************************************************************************/

#include "argz.h"

error_t argz_create_sep(const char *string, int sep, char **argz, size_t *argz_len) {

    int i;

    if (string == NULL) return ERROR; //if the input string is empty, pass the error

    *argz_len = strlen(string) + 1; // +1 for '\0'
    *argz = (char*)malloc(sizeof(char) * *argz_len);

    for (i = 0; i < *argz_len - 1; i++) {
        (*argz)[i] = string[i];
        if (string[i] == sep) (*argz)[i] = '\0';
    }

    (*argz)[i] = '\0'; //on the last position '\0'

    return OK; //or OK
}

size_t argz_count(const char *argz, size_t arg_len) {

    int i;
    int counter = 0;

    for (i = 0; i < arg_len; i++) {
        if (argz[i] == '\0') counter++;
    }

    return counter; //return counter vector
}

error_t argz_add(char **argz, size_t *argz_len, const char *str) {

    int size = 0;
    int i;

    if (str == NULL) return ERROR; //if the input string is empty, pass the error

    size = strlen(str) + 1;
    //adding strlen(size)
    *argz = (char*)realloc(*argz, (*argz_len + size) * sizeof(char));

    for (i = *argz_len; i < *argz_len + size; i++) (*argz)[i] = str[i - *argz_len];

    *argz_len += size;

    (*argz)[*argz_len] = '\0'; //on the last position '\0'

    return OK; //or OK
}

int find_firstEntry(char *argz, size_t argz_len, const char* entry) {

    int i;
    int firstEntry = -1;
    int firstTime = 1;
    int index = 0;
    int sizeEntry = strlen(entry);

    for (i = 0; i < argz_len && index < sizeEntry; i++) {
        if (argz[i] == entry[index]) {
            if (firstTime) {
                firstEntry = i;
                firstTime = 0;
            }
            index++;
        } else {
            index = 0;
            firstEntry = -1;
            firstTime = 1;
        }
    }

    return firstEntry; // return first entry
}

void argz_delete(char **argz, size_t *argz_len, char *entry) {

    int j;
    int i;
    int start;
    int sizeEntry;

    start = find_firstEntry(*argz, *argz_len, entry);

    if (start == -1 || entry == NULL) {
        printf("\nSorry, string not found in argz\n");
        return;// exit
    }

    sizeEntry = strlen(entry);

    for (i = 0; i < sizeEntry + 1; i++) {
        for (j = start; j < *argz_len; j++) (*argz)[j] = (*argz)[j + 1];
    }

    *argz_len -= sizeEntry + 1;

    *argz = (char*)realloc(*argz, *argz_len * sizeof(char));
}

error_t argz_insert(char **argz, size_t *argz_len, char *before, const char *entry) {

    int beforeIndex;
    int i;
    int j;
    int entrySize;

    if (before == NULL || entry == NULL) return ERROR;

    beforeIndex = find_firstEntry(*argz, *argz_len, before);
    if (beforeIndex == -1) {
        printf("\nSorry, string not found in argz\n");
        return ERROR;
    }

    entrySize = strlen(entry);
    *argz_len += entrySize + 1;

    *argz = (char *)realloc(*argz, *argz_len * sizeof(char));
    // +1 for '\0'
    for (i = 0; i < entrySize + 1; i++) {
        for (j = *argz_len; j > beforeIndex ; j--) (*argz)[j] = (*argz)[j - 1];
    }

    for (i = 0; i < entrySize; i++) (*argz)[beforeIndex + i] = entry[i];

    (*argz)[beforeIndex + entrySize] = '\0'; //on the last position '\0'
}

char * argz_next(char *argz, size_t argz_len, const char *entry) {
    int start;

    if (entry == NULL) return &(argz[0]);

    start = find_firstEntry(argz, argz_len, entry);
    if (start == -1) return 0;

    while (argz[start] != '\0') start++;

    if (start >= argz_len - 1) return 0;

    return &(argz[start + 1]);
}

error_t argz_replace(char **argz, size_t *argz_len, const char *str, const char *with) {
    if (str == NULL || with == NULL) return ERROR;

    //inserting with before str
    int beforeIndex;
    int i;
    int j;
    int entrySize;
    int start;
    int sizeEntry;

    beforeIndex = find_firstEntry(*argz, *argz_len, str);

    if (beforeIndex == -1) {
        printf("\nSorry, string not found in argz\n");
        return ERROR;
    }

    entrySize = strlen(with);
    *argz_len += entrySize;

    *argz = (char *)realloc(*argz, *argz_len * sizeof(char));

    // +1 for '\0'
    for (i = 0; i < entrySize + 1; i++) {
        for (j = *argz_len; j > beforeIndex; j--) (*argz)[j] = (*argz)[j - 1];
    }

    for (i = 0; i < entrySize; i++) (*argz)[beforeIndex + i] = with[i];

    (*argz)[beforeIndex + entrySize] = '\0'; //on the last position '\0'

    start = find_firstEntry(*argz, *argz_len, str);

    sizeEntry = strlen(str);

    for (i = 0; i < sizeEntry + 1; i++) {
        for (j = start; j < *argz_len; j++) (*argz)[j] = (*argz)[j + 1];
    }

    *argz_len -= sizeEntry;

    *argz = (char*)realloc(*argz, *argz_len * sizeof(char));

    return OK;
}

void argz_print(const char *argz, size_t argz_len) {
    int i;

    for (i = 0; i < argz_len; i++) printf("%c", argz[i]);

    printf("\n");
}