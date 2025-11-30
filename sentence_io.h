#pragma once
#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#define SENT_BUFF 16;

typedef struct sentence
{
    wchar_t* str;
    size_t capacity;
} sentence_t;

sentence_t* scan_sentence();