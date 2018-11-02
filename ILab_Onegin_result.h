#ifndef UNTITLED_ILAB_ONEGIN_RESULT_H
#define UNTITLED_ILAB_ONEGIN_RESULT_H



#include <stdio.h>
#include <math.h>
#include <mm_malloc.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#include "ILab_Onegin_structures.h"


void* Array_cpy (string*, string_buffer*);
void Onegin_result (string*, char**, char**, string_buffer*);



void* Array_cpy (string* text, string_buffer* bufpar)
{
    char** new_array = (char**) calloc(bufpar->nstr, sizeof(char*));

    if (new_array == NULL) exit(5);

    for (int i = 0; i < bufpar->nstr; i++)
    {
        new_array[i] = text[i].str;
    }

    return new_array;
}





void Onegin_result (string* text, char** sort1, char** sort_alpha, string_buffer* bufpar)
{
    FILE* result = fopen ("../Data/Onegin_result.txt", "w");

    fprintf (result, "--Rhyme sorting:\n\n\n");

    for (int i = 0; i < bufpar->nstr; i++)
    {
        fprintf (result, "%s\n", text[i].str);
    }

    fprintf (result, "\n\n--Alphabet sorting:\n\n\n");

    for (int i = 0; i < bufpar->nstr; i++)
    {
        fprintf (result, "%s\n", sort_alpha[i]);
    }

    fprintf (result, "\n\n--Original:\n\n\n");

    for (int i = 0; i < bufpar->nstr; i++)
    {
        fprintf (result, "%s\n", sort1[i]);
    }

    fclose (result);
}

#endif
