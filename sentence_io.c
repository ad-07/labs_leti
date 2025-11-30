#include "sentence_io.h"

sentence_t* scan_sentence(){
    wchar_t one_wchar;
    size_t size = SENT_BUFF;
    wchar_t* sentence = (wchar_t*)malloc(size * sizeof(wchar_t));


    if (sentence == NULL) {
        fprintf(stderr, "Error: Failed to allocate initial memory\n");
        return NULL;
    }
    
    size_t wchar_count = 0;
    do{
        one_wchar = getwchar();
    }while(one_wchar == L' ' || one_wchar == L'\t');

    sentence[wchar_count++] = one_wchar;
    
    while(one_wchar != L'.' && one_wchar != L'!' && one_wchar != L'?' && one_wchar != L'\n'){
        if(wchar_count >= size-2){
            size *= 2;
            wchar_t* tmp_sentence = (wchar_t*)realloc(sentence, size*sizeof(wchar_t));
            if (tmp_sentence == NULL) {
                fprintf(stderr, "Error: Failed to allocate initial memory\n");
                free(sentence);
                return NULL;
            }
            sentence = tmp_sentence;
        }
        one_wchar = getwchar();
        sentence[wchar_count++] = one_wchar;

    };
    sentence[wchar_count] = '\0';

    sentence_t* result_sentence = (sentence_t*)malloc(sizeof(sentence_t));
    if (result_sentence == NULL) {
        fprintf(stderr, "Error: Failed to allocate initial memory\n");
        free(sentence);
        return NULL;
    }
    result_sentence->str = sentence;
    result_sentence->capacity = size;

    return result_sentence;
}