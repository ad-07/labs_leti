#pragma once
#include "text_io.h"
#include "sentence_io.h"
void print_help();
void print_text(text_t* text);
int is_letter(wchar_t wchar);
int count_words_in_sentence(wchar_t* sentence);

void replace_ending(text_t* text);

text_t* find_second_word_of_first_sentence(text_t* text);
text_t* sentences_more_10_words(text_t* text);
int cmp_by_len_words(const void* a, const void* b);
void sentence_to_lower(wchar_t* sentence);
wchar_t* second_word_of_first_sentence(wchar_t* sentence);
void print_sentences_with_second_word(text_t* text);