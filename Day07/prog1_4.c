#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str_func.h"

int main() {
    int chx, argv;
    bool flg = true;
    char *sentence, x, *str2, *str3, *res, **args;

    while(flg) {
        printf("\n");
        printf("1. Remove Letters\n");
        printf("2. Find and Replace\n");
        printf("3. Reverse Sentence\n");
        printf("4. String Formatting\n");
        printf("0. Exit\n");

        printf("\nEnter choice: ");
        scanf("%d", &chx);
        clr_buffr();

        switch(chx) {
            case 0:
                flg = false;
                break;
            case 1:
                sentence = input_str();
                printf("enter char to remove: ");
                scanf("%c", &x);
                clr_buffr();
                res = remove_letter(sentence, x);
                printf("Result: %s\n", res);
                free(sentence);
                free(res);
                break;
            case 2:
                printf("Enter the sentence:\n");
                sentence = input_str();
                printf("Enter word to replace:\n");
                str2 = input_str();
                printf("Enter replacement:\n");
                str3 = input_str();
                res = replace_word(sentence, str2, str3);
                printf("Result: %s\n", res);
                free(sentence);
                free(str2);
                free(str3);
                free(res);
                break;
            case 3:
                sentence = input_str();
                res = reverse_sentence(sentence);
                printf("Result: %s\n", res);
                free(sentence);
                free(res);
                break;
            case 4:
                printf("Enter the sentence:\n");
                sentence = input_str();
                printf("Enter number of arguments: ");
                scanf("%d", &argv);
                clr_buffr();
                args = malloc(argv*sizeof(char *));
                if (args == NULL) {
                    printf("MEMORY ALLOCATION ERROR.\n");
                    exit(-1);
                }
                for(int i=0; i<argv; i++) {
                    args[i] = input_str();
                }
                res = format_str(sentence, args, argv);
                printf("Result: %s\n", res);

                for(int i=0; i<argv; i++) {
                    free(args[i]);
                }
                free(args);
                free(sentence);
                free(res);
                break;
            default:
                printf("Invalid Input.\n");
        }
    }
    return 0;
}