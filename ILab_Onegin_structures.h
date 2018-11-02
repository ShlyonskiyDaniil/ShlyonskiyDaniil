#ifndef UNTITLED_ILAB_ONEGIN_STRUCTURES_H
#define UNTITLED_ILAB_ONEGIN_STRUCTURES_H



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

#endif
