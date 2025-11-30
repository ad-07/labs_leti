#include "sentence_io.h"
#include "text_io.h"
#include "functions.h"



int main(){
    const float V = 5.9;
    const wchar_t* Name = L"Anatoliy";
    const wchar_t* Surname = L"Dirxen";
    setlocale(LC_ALL, "");
    wprintf(L"Course work for option %.1f, created by %ls %ls.\n", V, Name, Surname);

    int task_num;
    scanf("%d", &task_num);
    if(task_num == 5){
        print_help();
        return 0;
    }

    text_t* scanned_text = scan_text();
     if (scanned_text == NULL) {
        fprintf(stderr, "Error: Failed to create scanned_text\n");
        return 1;
    }
    switch (task_num){
        case 0:
            print_text(scanned_text);
            break;
        case 1:
            replace_ending(scanned_text);
            print_text(scanned_text);
            break;
        case 2:
            print_sentences_with_second_word(scanned_text);
            break;
        case 3:
            qsort(scanned_text->sentences, scanned_text->sentences_count, sizeof(sentence_t*), cmp_by_len_words);
            print_text(scanned_text);
            break;
        case 4:
            print_text(sentences_more_10_words(scanned_text));
            break;
        default:
            fprintf(stderr, "Error: Invalid task number\n");
            break;
        }
}