#ifndef STR_FUNC_H
#define STR_FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum bool {
    false = 0,
    true = 1
};
typedef enum bool bool;


char *format_str(char *description, char **values, int argv);
void reverse_sequence(char *seq, int begin_indx, int end_indx);
char *reverse_sentence(char *sentence);
int *calc_lps(char *pattern);
int *kmp_search(char *text, char *pattern, int *no_of_matches);
char *replace_word(char *sentence, char *target, char *replacement);
bool find_in_arr(int *arr, int arr_size, int target);
char *remove_letter(char *sentence, char letter);
char *input_str();
void clr_buffr();

#endif