#include "functions.h"
#include <string.h>

void print_help(){
    printf("Справка о функциях, числа – номера команды:\n");
    printf("0 - Вывод текста после первичной обязательной обработки\n\n");
    printf("1 - Изменить все слова в тексте заканчивающиеся на \"ться\"\n"
            "    так чтобы они заканчивались на \"тся\" и наоборот.\n"
            "    Поиск \"ться\" и \"тся\" осуществлять без учёта регистра.\n"
            "    Замену производить на нижний регистр.\n"
            "    Пример: \"ТьсЯ\" -> \"тся\"\n\n");
    printf("2 - Вывести все предложения, в которых встречается\n"
            "    второе слово первого предложения (без учёта регистра).\n"
            "    Данное слово необходимо выделить зеленым цветом.\n"
            "    Первое предложение выводить не нужно.\n\n");
    printf("3 - Отсортировать предложения по возрастанию\n"
            "    количества слов в предложении.\n"
            "    В случае равенства сохранить порядок вхождения.\n\n");
    printf("4 - Удалить все предложения в которых больше 10 слов.\n\n");
    printf("5 - Вывод этой справки\n");
}

void print_text(text_t* text){
    size_t limit = text->sentences_count;
    for(size_t i = 0; i<limit; ++i){
        wprintf(L"%ls\n", text->sentences[i]->str);
    }
}


void sentence_to_lower(wchar_t* sentence){
    if (!sentence) return;
    while (*sentence) {
        *sentence = towlower(*sentence);
        sentence++;
    }
}


void replace_ending(text_t* text){
    if(!text || !text->sentences) return;
    size_t limit = text->sentences_count;

    for(size_t i = 0; i<limit; ++i){
        int str_size = wcslen(text->sentences[i]->str);

        wchar_t* lower_sentence = wcsdup(text->sentences[i]->str);
        if(lower_sentence == NULL){
            fprintf(stderr, "Error: Failed to allocate memory in wcsdup\n");
            return;
        }

        sentence_to_lower(lower_sentence);
        wchar_t punctuation = lower_sentence[str_size-1];
        if(str_size>4 && wcsncmp(lower_sentence + str_size-5, L"ться", 4) == 0){

            wcscpy(text->sentences[i]->str + str_size-5, L"тся");

            text->sentences[i]->str[str_size-2] = punctuation;
            text->sentences[i]->str[str_size-1] = L'\0';
        }
        else if(str_size>3 && wcsncmp(lower_sentence + str_size-4, L"тся", 3) == 0){

            wcscpy(text->sentences[i]->str + str_size-4, L"ться");
            text->sentences[i]->str[str_size] = punctuation;
            text->sentences[i]->str[str_size+1] = L'\0';
        }
        free(lower_sentence);
    }
}

int is_letter(wchar_t wchar){
    if(iswalnum(wchar) || (wchar >= L'А' && wchar <= L'я') || 
        wchar == L'ё' || wchar == L'Ё' || wcschr(L"@\"$#№%^*_-", wchar)){
            return 1;
    }
    return 0;
}


int count_words_in_sentence(wchar_t* sentence){
    if (!sentence) return 0;
    int count_words = 0, i=0;
    int limit = wcslen(sentence);
    while(i<limit && !is_letter(sentence[i])){
        ++i;
    }
    while(i<limit){
        if(!is_letter(sentence[i])){
            ++count_words;
            while(i< limit && !is_letter(sentence[i])){
                ++i;
            }
        }else{
            ++i;
        }
    }
    return count_words;
}


int cmp_by_len_words(const void* a, const void* b){

    const sentence_t* str_a = *(const sentence_t**)a;
    const sentence_t* str_b = *(const sentence_t**)b;

    const int count_words_str_a = count_words_in_sentence(str_a->str);
    const int count_words_str_b = count_words_in_sentence(str_b->str);
    if(count_words_str_a > count_words_str_b){
        return -1;
    }
    if(count_words_str_a < count_words_str_b){
        return 1;
    }
    return 0;
}


text_t* sentences_more_10_words(text_t* text){
    if(!text || !text->sentences) return NULL;
    sentence_t** res_sentences = (sentence_t**)malloc(text->capacity*sizeof(sentence_t*));
    if(res_sentences == NULL){
            fprintf(stderr, "Error: Failed to allocate memory in sentences_more_10_words\n");
            return NULL;
        }
    sentence_t** start_sentences = text->sentences;
    size_t limit = text->sentences_count, count_res_sentences = 0;
    for(size_t i = 0; i<limit; ++i){
        if(count_words_in_sentence(start_sentences[i]->str)>10){
            res_sentences[count_res_sentences] = malloc(sizeof(sentence_t));
            if(res_sentences[count_res_sentences] == NULL){
                fprintf(stderr, "Error: Failed to allocate memory in sentences_more_10_words\n");
                for(size_t j = 0; j < count_res_sentences; ++j) {
                    free(res_sentences[j]);
                }
                free(res_sentences);
                return NULL;
            }

            res_sentences[count_res_sentences]->str = start_sentences[i]->str;
            ++count_res_sentences;
        }
    }
    text_t* result_text = (text_t*)malloc(sizeof(text_t));
    if(result_text == NULL){
        fprintf(stderr, "Error: Failed to allocate memory in sentences_more_10_words\n");
        free(res_sentences);
        return NULL;
    }
    result_text->sentences = res_sentences;
    result_text->capacity = text->capacity;
    result_text->sentences_count = count_res_sentences;
    return result_text;
}



wchar_t* second_word_of_first_sentence(wchar_t* sentence){
    if(!sentence){
        return NULL;
    }
    wchar_t* lower_sentence = wcsdup(sentence);
    if(lower_sentence == NULL){
        fprintf(stderr, "Error: Failed to allocate memory in second_word_of_first_sentence\n");
        return NULL;
    }
    sentence_to_lower(lower_sentence);

    int count_words = 0, i=0, word_id_start = 0, word_id_end = 0;
    int limit = wcslen(lower_sentence);
    while(i<limit && !is_letter(lower_sentence[i])){
        ++i;
    }
    while(i<limit){
        if(!is_letter(lower_sentence[i])){
            ++count_words;
            if(count_words == 2){
                word_id_end = i-1;
                break;
            }
            while(i< limit && !is_letter(lower_sentence[i])){
                ++i;
            }
            if(count_words==1){
                word_id_start = i;
            }
            
        }else{
            ++i;
        }
    }
    int length = word_id_end-word_id_start+1;
    if(length <= 0){
        free(lower_sentence);
        return NULL;
    }
    wchar_t* word = malloc(length*sizeof(wchar_t));
    if(word == NULL){
        fprintf(stderr, "Error: Failed to allocate memory in second_word_of_first_sentence\n");
        free(lower_sentence);
        return NULL;
    }
    wcsncpy(word, lower_sentence+word_id_start, length);
    word[length] = L'\0';
    free(lower_sentence);
    return word;
}


void print_sentences_with_second_word(text_t* text){
    int limit = text->sentences_count;
    if(text->sentences_count<1){
        fprintf(stderr, "Error: Failed to get first word in print_sentences_with_second_word\n");
        return;
    }

    wchar_t* word = second_word_of_first_sentence(text->sentences[0]->str);
    if(word == NULL){
        fprintf(stderr, "Error: Failed to allocate memory in print_sentences_with_second_word\n");
        return;
    }

    for(int i =0; i<limit; ++i){
        wchar_t* lower_sentence = wcsdup(text->sentences[i]->str);
        wchar_t* lower_ptr = lower_sentence;
        if(lower_sentence == NULL){
            fprintf(stderr, "Error: Failed to allocate memory in print_sentences_with_second_word\n");
            continue;
        }

        sentence_to_lower(lower_sentence);
        wchar_t* found;
        wchar_t* scan_ptr = lower_sentence;

        if((found = wcsstr(lower_sentence, word)) != NULL){
            do{
                int position = found - scan_ptr;
                wchar_t temp = *found;
                *found = L'\0';
                wprintf(L"%ls", scan_ptr);
                *found = temp;  
                wprintf(L"\033[32m%ls\033[0m", word);
                scan_ptr = found + wcslen(word);
            }while((found = wcsstr(scan_ptr, word)) != NULL);
            wprintf(L"%ls\n", scan_ptr);
        }
        
        free(lower_ptr);
    }
    free(word);

}