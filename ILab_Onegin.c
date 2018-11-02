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


struct string_buffer String_buffer_create(void);
struct string_buffer Formation (string_buffer);
string* Division (string_buffer*);
int Encoding (void*);
int String_buffer_cmp (const void*, const void*);
int Vice_versa_cmp (const void* , const void*);
unsigned long Min (unsigned long , unsigned long);
void* Array_cpy (string*, string_buffer*);
void Onegin_result (string*,  char**, char**, string_buffer*);





//////////////////////
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
/////////////////////






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





string* Division (string_buffer *bufpar)
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


    for (int i = 0; i < bufpar->nstr; i++)
    {
        fprintf (result, "%s\n", text[i].str);
    }

    fprintf (result, "\n\n");

    for (int i = 0; i < bufpar->nstr; i++)
    {
        fprintf (result, "%s\n", sort_alpha[i]);
    }

    fprintf (result, "\n\n");

    for (int i = 0; i < bufpar->nstr; i++)
    {
        fprintf (result, "%s\n", sort1[i]);
    }

    fclose (result);
}

