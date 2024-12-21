#include "../minishell.h"

char *expand_variable(const char *value, int *i, char *result, int *out_index) {
    int var_start = *i + 1; // Salta il simbolo '$'
    while (isalnum(value[var_start]) || value[var_start] == '_') {
        var_start++;
    }
    char *var_name = strndup(value + *i + 1, var_start - *i - 1);
    char *var_value = getenv(var_name);
    if (var_value) {
        strcpy(result + *out_index, var_value);
        *out_index += strlen(var_value);
    }
    free(var_name);
    *i = var_start - 1; // Aggiorna l'indice i alla fine del nome della variabile
    return result;
}

char *process_character(const char *value, int *i, int *in_single_quotes, int *in_double_quotes, char *result, int *out_index) {
    char current_char = value[*i];
    if (current_char == '\'' && !*in_double_quotes) {
        *in_single_quotes = !*in_single_quotes; // Toggle state of single quotes
        return result;
    } else if (current_char == '\"' && !*in_single_quotes) {
        *in_double_quotes = !*in_double_quotes; // Toggle state of double quotes
        return result;
    } else if (current_char == '$' && !*in_single_quotes && (isalnum(value[*i + 1]) || value[*i + 1] == '_')) {
        return expand_variable(value, i, result, out_index);
    }
    result[(*out_index)++] = current_char;
    return result;
}

char *expand_token_value(const char *value) {
    if (!value) return NULL;
    char *result = malloc(strlen(value) * 2 + 1);
    if (!result) return NULL;

    int out_index = 0;
    int in_single_quotes = 0, in_double_quotes = 0;

    for (int i = 0; value[i]; i++) {
        process_character(value, &i, &in_single_quotes, &in_double_quotes, result, &out_index);
    }
    result[out_index] = '\0';
    return result;
}

