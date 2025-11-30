#pragma once
#include "sentence_io.h"
#define TEXT_BUFF 16;

typedef struct text
{
    sentence_t** sentences;
    size_t sentences_count;
    size_t capacity;
} text_t;

int strcmp_by_lower_wchar(wchar_t* str1, wchar_t* str2);
void cleaner(sentence_t** text, int local_sentences_count);
text_t* scan_text();
