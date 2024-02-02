#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str_func.h"

char *format_str(char *description, char **values, int argv) {
    int len, i, indx, new_len=0, prev_len, word_size;
    char *res = NULL, *end = NULL, *word;

    len = strlen(description);

    indx = 0;
    i = 0;
    while (i<len) {
        // printf("i: %d\n", i);
        if (description[i] == '$') {
            i++;
            indx = strtol(&description[i], &end, 10);
            // printf("Indx: %d, ", indx);
            // check out of bounds
            if (indx >= argv || indx < 0) {
                word = "ERROR";
            } else {
                word = values[indx];
            }
            prev_len = new_len;
            word_size = strlen(word);
            new_len += word_size;

            res = realloc(res, new_len*sizeof(char));
            if (res == NULL) {
                printf("MEMORY ALLOCATION ERROR.\n");
                exit(-1);
            }

            for (int k=0; k<word_size; k++) {
                res[prev_len+k] = word[k];
            }
            // incr i
            // while (&description[i] != end) i++;
            i = (int)((int)(end - description) / sizeof(char));
        } else {
            new_len++;
            res = realloc(res, new_len*sizeof(char));
            if (res == NULL) {
                printf("MEMORY ALLOCATION ERROR.\n");
                exit(-1);
            }
            res[new_len - 1] = description[i];
            i++;
        }
    }
    return res;
}

void reverse_sequence(char *seq, int begin_indx, int end_indx) {
    int i, j;
    char tmp;
    i = begin_indx;
    j = end_indx;

    while(i < j) {
        tmp = seq[i];
        seq[i] = seq[j];
        seq[j] = tmp;
        i++;
        j--;
    }
}

char *reverse_sentence(char *sentence) {
    char *res = NULL;
    int i, j;
    int len = strlen(sentence);

    res = malloc((len+1)*sizeof(char)); // +1 for '\0'
    if (res == NULL) {
        printf("MEMORY ALLOCATION ERROR.\n");
        exit(-1);
    }

    strcpy(res, sentence);
    i = 0;
    j = 0;

    while(j<(len+1)) {
        if(res[j] == ' ' || res[j] == '\0' || res[j] == '\n') {
            reverse_sequence(res, i, j-1);
            j++;
            i = j;
        } else {
            j++;
        }
    }

    reverse_sequence(res, 0, len-1); // -1 to not reverse the '\0'

    return res;
}

int *calc_lps(char *pattern) {
    int *lps = NULL, m, curr_len, i;

    m = strlen(pattern);
    lps = calloc(m, sizeof(int)); // calloc will initialise to 0
    if (lps == NULL) {
        printf("MEMORY ALLOCATION ERROR.\n");
        exit(-1);
    }
    curr_len = 0;
    i = 1;

    while (i < m) {
        if (pattern[curr_len] == pattern[i]) {
            curr_len++;
            lps[i] = curr_len;
            i++;
        } else {
            if (curr_len > 0) {
                // i.e. this will keep executing (due to outer loop) till curr_len becomes 0
                curr_len = lps[curr_len - 1];
            }
            else {
                // i.e. when curr_len has become 0
                lps[i] = 0;
                i++;
            }
        }
    }

    return lps;
}

int *kmp_search(char *text, char *pattern, int *no_of_matches) {
    int m, n, i, j, *lps = NULL, *result = NULL;
    n = strlen(text);
    m = strlen(pattern);
    lps = calc_lps(pattern);
    *no_of_matches = 0;
    i = j = 0;

    while (i < n){
        if (pattern[j] == text[i]){
            i++;
            j++;
        }
        if (j == m) {
            (*no_of_matches)++;
            result = realloc(result, (*no_of_matches)*sizeof(int));
            if (result == NULL) {
                printf("MEMORY ALLOCATION ERROR.\n");
                exit(-1);
            }
            result[(*no_of_matches)-1] = i - j;
            j = lps[j - 1];
        }
        else if (i < n && pattern[j] != text[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
    free(lps);

    return result;
}

char *replace_word(char *sentence, char *target, char *replacement) {
    int *indices, no_of_matches, old_len, new_len=0, i, prev;
    char *res = NULL;

    old_len = strlen(sentence);
    indices = kmp_search(sentence, target, &no_of_matches);

    i = 0;
    while (i<old_len+1) { //+1 for '\0'
        if (find_in_arr(indices, no_of_matches, i)) {
            // replace
            prev = new_len;
            new_len += strlen(replacement);
            res = realloc(res, new_len*sizeof(char));
            if (res == NULL) {
                printf("MEMORY ALLOCATION ERROR.\n");
                exit(-1);
            }

            for (int k=prev; k<new_len; k++) {
                res[k] = replacement[k-prev];
            }
            // incr i appropraitely
            i += strlen(target);
        } else {
            new_len++;
            res = realloc(res, new_len*sizeof(char));
            if (res == NULL) {
                printf("MEMORY ALLOCATION ERROR.\n");
                exit(-1);
            }
            res[new_len-1] = sentence[i];
            i++;
        }
    }
    free(indices);

    return res;
}

bool find_in_arr(int *arr, int arr_size, int target) {
    bool found = false;

    for (int i=0; i<arr_size; i++) {
        if (arr[i] == target) {
            found = true;
            break;
        }
    }

    return found;
}

char *remove_letter(char *sentence, char letter) {
    char *res = NULL;
    int old_len, new_len = 0;

    old_len = strlen(sentence);

    for (int i=0; i<old_len+1; i++) { // old_len+1 to scan and add '\0' at end
        if (sentence[i] == letter) {
            continue;
        } else {
            new_len++;
            res = realloc(res, new_len*sizeof(char));
            if (res == NULL) {
                printf("MEMORY ALLOCATION ERROR.\n");
                exit(-1);
            }
            res[new_len-1] = sentence[i];
        }
    }

    return res;
}

char *input_str() {
    char *res = NULL, x;
    int size = 0;

    printf("Enter the string: ");
    do {
        x = getchar();
        size++;
        res = realloc(res, size*sizeof(char));
        if (res == NULL) {
            printf("MEMORY ALLOCATION ERROR.\n");
            exit(-1);
        }

        if (x != '\n') {
            res[size-1] = x;
        } else {
            res[size-1] = '\0';
        }
    } while(x != '\n');

    return res;
}

void clr_buffr() {
    char x;
    do {
        x = getchar();
    } while(x != '\n');
}