#ifndef UNTITLED_ILAB_ONEGIN_FILE_1_H
#define UNTITLED_ILAB_ONEGIN_FILE_1_H



#include <stdio.h>
#include <math.h>
#include <mm_malloc.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#include "ILab_Onegin_structures.h"



struct string_buffer Formation (struct string_buffer);
string* Division (string_buffer*);



struct string_buffer String_buffer_create (void)
{
    string_buffer bufpar;

    bufpar.nchars = 0;
    bufpar.buf = NULL;


    FILE* Onegin = fopen("../Data/Onegin.txt", "r");


    if (Onegin == NULL)
    {
        printf("File Onegin can't be opened!\n");
        exit(0);
    }


    // Finding buf size.
    fseek(Onegin, 0, SEEK_END);
    bufpar.nchars = (unsigned int) ftell(Onegin);


    // Text transfering to buf.
    bufpar.buf = (char*) calloc(bufpar.nchars, sizeof(char));

    if (bufpar.buf == NULL) exit(1);

    if (bufpar.buf == NULL) exit(2);

    fseek(Onegin, 0, SEEK_SET);

    if (fread (bufpar.buf, sizeof(char), bufpar.nchars, Onegin) != bufpar.nchars)
    {
        if (feof(Onegin) == 0)
        {
            printf("Premature file ending!\n");
        }
        else printf("File read error!\n");

        exit(3);
    }


    return bufpar;
}





struct string_buffer Formation (struct string_buffer bufpar)
{
    bufpar.nstr = 0;

    for (int i = 0; i < bufpar.nchars; i++)
    {
        if (bufpar.buf[i] == '\n')
            bufpar.nstr++;

        while (bufpar.buf[i] == '\n')
        {
            bufpar.buf[i] = '\0';
            i++;
        }
    }

    return bufpar;
}





string* Division (string_buffer* bufpar)
{
    struct string* text = (struct stirng*) calloc(bufpar->nstr, sizeof(struct string));

    if (text == NULL) exit(4);

    // Заполняем text адресами начала строк и находим длину каждой из них.
    text[0].str = bufpar->buf;
    int j = 1;
    unsigned int length = 0;

    for (int i = 0; i < bufpar->nchars; i++)
    {
        if (bufpar->buf[i] == '\0')
        {
            text[j - 1].str_len = length;

            while (bufpar->buf[i] == '\0') i++;
            text[j].str = bufpar->buf + i;

            j++;

            length = 0;
            continue;
        }

        length++;
    }

    return text;
}

#endif