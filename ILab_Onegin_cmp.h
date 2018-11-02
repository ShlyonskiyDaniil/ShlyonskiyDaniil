#ifndef UNTITLED_ILAB_ONEGIN_FILE_CMP_H
#define UNTITLED_ILAB_ONEGIN_FILE_CMP_H



#include <stdio.h>
#include <math.h>
#include <mm_malloc.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#include "ILab_Onegin_structures.h"



int Encoding (void*);
int String_buffer_cmp (const void*, const void*);
int Vice_versa_cmp (const void*, const void*);
unsigned long Min(unsigned long, unsigned long );



int Encoding (void* str)
{
    char alph[] = {"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя\n"};

    for (int i = 0; i < strlen(alph) - 1; i++)
    {
        if (*((char*)str) == alph[i]) return i + 1;
    }

    return 0;
}





int String_buffer_cmp (const void* struct1_ptr, const void* struct2_ptr)
{
    string* struct_str1 = (string*)struct1_ptr;
    string* struct_str2 = (string*)struct2_ptr;

    char* str1 = struct_str1->str;
    char* str2 = struct_str2->str;

    for(int i = 0; i > -1; i++)
    {
        if(*str1 == '\0')
        {
            return -1;
        }

        if(*str2 == '\0')
        {
            return 1;
        }

        while (Encoding(str1) == 0) str1++;
        while (Encoding(str2) == 0) str2++;

        if (Encoding(str1) != Encoding(str2))
        {
            return Encoding(str1) - Encoding(str2);
        }

        str1++;
        str2++;
    }
    return 99999;
}





int Vice_versa_cmp (const void* struct1_ptr, const void* struct2_ptr)
{
    string* struct_str1 = (string*)struct1_ptr;
    string* struct_str2 = (string*)struct2_ptr;

    unsigned int len1 = struct_str1->str_len;
    unsigned int len2 = struct_str2->str_len;

    char* str1 = struct_str1->str + len1 - 1;
    char* str2 = struct_str2->str + len2 - 1;

    for (int i = 0; i < Min(len1, len2); i++)
    {
        while (Encoding(str1) == 0) str1--;
        while (Encoding(str2) == 0) str2--;

        if (Encoding(str1) != Encoding(str2))
        {
            return Encoding(str1) - Encoding(str2);
        }

        str1--;
        str2--;
    }
    return 99999;
}





unsigned long Min(unsigned long a, unsigned long b)
{
    if (a > b) return b;

    return a;
}

#endif
