#include <stdio.h>
#include <math.h>
#include <mm_malloc.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#include "ILab_Onegin_manufacturing.h"
#include "ILab_Onegin_cmp.h"
#include "ILab_Onegin_result.h"
#include "ILab_Onegin_structures.h"



int main()
{
    string_buffer bufpar = String_buffer_create();
    bufpar = Formation(bufpar);

    string* text = Division(&bufpar);
    char** sort1 = (char**) Array_cpy(text, &bufpar);

    qsort(text, bufpar.nstr, sizeof(string), String_buffer_cmp);
    char** sort_alpha = (char**) Array_cpy(text, &bufpar);

    qsort(text, bufpar.nstr, sizeof(string), Vice_versa_cmp);

    Onegin_result (text, sort1, sort_alpha, &bufpar);

    free(bufpar.buf);
    free(text);
    free(sort1);
    free(sort_alpha);
}