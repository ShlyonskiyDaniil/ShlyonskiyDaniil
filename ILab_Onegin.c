#include <stdio.h>
#include <math.h>
#include <mm_malloc.h>
#include <string.h>
#include <assert.h>
#include <limits.h>


typedef struct string_buffer
{
    unsigned long nchars ;
    char* buf;
    unsigned long  nstr;
} string_buffer;

typedef struct string
{
    char* str;
    unsigned int str_len;
}string;


struct string_buffer string_buffer_create(void);
struct string_buffer formation (string_buffer);
string* division (string_buffer*);
int encoding (void*);
int string_buffercmp (const void*, const void* );

//////////////////////
int main()
{
    string_buffer bufpar = string_buffer_create();
    bufpar = formation(bufpar);
    string* text = division(&bufpar);

    qsort(text->str, bufpar.nstr, sizeof(char*), string_buffercmp);

    for (int i = 0; i < bufpar.nstr; i++)
    {
        printf("%s\n", text[i].str);
    }



    free(bufpar.buf);
    free(text);
}
/////////////////////






struct string_buffer string_buffer_create(void)
{
    string_buffer bufpar;

    bufpar.nchars = 0;
    bufpar.buf = NULL;


    FILE* Onegin = fopen("../Data/Onegin.txt", "r");


    if (Onegin == NULL)
    {
        printf("File Onegin can't be opened!\n");
        exit(1);
    }


    // Finding buf size.
    fseek(Onegin, 0, SEEK_END);
    bufpar.nchars = (unsigned int)ftell(Onegin);


    // Text transfering to buf.
    bufpar.buf = (char*)calloc(bufpar.nchars, sizeof(char));

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





struct string_buffer formation (struct string_buffer bufpar)
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





string* division (string_buffer *bufpar)
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





int encoding (void* str)
{
    char alph[] = {"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя\n"};

    for (int i = 0; i < strlen(alph) - 1; i++)
    {
        if (*((char*)str) == alph[i]) return i + 1;
    }

    return 0;
}





int string_buffercmp (const void* text_ptr1, const void* text_ptr2)
{
    char* str1 = *(char**) text_ptr1;
    char* str2 = *(char**) text_ptr2;

    for(int i = 0; i > -1; i++)
    {
        if(str1[i] == '\0')
        {
            return -1;
        }

        if(str2[i] == '\0')
        {
            return 1;
        }

        while (encoding(str1) == 0) str1++;
        while (encoding(str2) == 0) str2++;

        if (encoding(str1) != encoding(str2))
        {
            return encoding(str1) - encoding(str2);
        }

        str1++;
        str2++;
    }
    return 99999;
}