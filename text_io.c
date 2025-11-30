#include "text_io.h"



int strcmp_by_lower_wchar(wchar_t* str1, wchar_t* str2){
    while(*str1 && *str2){
        if(towlower(*str1) != towlower(*str2)){
            return 0;
        }
        ++str1;
        ++str2;
    }
    return *str1 == *str2;
}

void cleaner(sentence_t** text, int local_sentences_count){
    for(size_t j = 0; j < local_sentences_count; ++j){
        free(text[j]->str); 
        free(text[j]);
    }    
    free(text);
}

text_t* scan_text(){
    size_t size = TEXT_BUFF;
    sentence_t* one_sentence;
    sentence_t** text = (sentence_t**)malloc(size * sizeof(sentence_t*));


    if (text == NULL) {
        fprintf(stderr, "Error: Failed to allocate initial memory\n");
        return NULL;
    }
    size_t local_sentences_count = 0, empty_sentences_count=0;
    do{
        if(local_sentences_count == size-1){
            size *= 2;
            sentence_t** tmp_text = (sentence_t**)realloc(text, size*sizeof(sentence_t*));
            if (tmp_text == NULL) {
                fprintf(stderr, "Error: Failed to allocate initial memory\n");
                cleaner(text, local_sentences_count);
                return NULL;
            }
            text = tmp_text;
        }
        one_sentence = scan_sentence();
        if (one_sentence == NULL) {
                cleaner(text, local_sentences_count);

                fprintf(stderr, "Error: Failed to scan sentence\n");
                return NULL;
            }
        if(one_sentence->str[0] == L'\n'){
            ++empty_sentences_count;
            free(one_sentence->str);
            free(one_sentence);
        }else{
            empty_sentences_count = 0;
            int is_duplicate = 0;
            for(int i =0; i<local_sentences_count; ++i){
                if(strcmp_by_lower_wchar(one_sentence->str, text[i]->str)){
                    is_duplicate = 1;
                    break;
                }
            }
            if(!is_duplicate){
                text[local_sentences_count] = one_sentence;
                ++local_sentences_count;
            }else if(is_duplicate){
                free(one_sentence->str);
                free(one_sentence);
                continue;
            }
        }

    }while(empty_sentences_count < 2);

    text_t* result_text = (text_t*)malloc(sizeof(text_t));
    if(result_text == NULL){
        fprintf(stderr, "Error: Failed to reallocate memory in scan_text\n");
        cleaner(text, local_sentences_count);

        return NULL;
    }
    result_text->sentences = text;
    result_text->capacity = size;
    result_text->sentences_count = local_sentences_count;

    return result_text;
}