#include "../minishell.h"

// Funzione di espansione specifica per tokens
char *expand_token_value(const char *value) {
    if (!value) return NULL;
    char *result = malloc(strlen(value) * 2 + 1);  // Allocazione eccessiva per sicurezza
    int out_index = 0;
    int in_single_quotes = 0, in_double_quotes = 0;

    for (int i = 0; value[i]; i++) {
        switch (value[i]) {
            case '\'':  // Gestione delle virgolette singole
                if (!in_double_quotes) {
                    in_single_quotes ^= 1;
                    continue;  // Non includere l'apice nel risultato finale
                }
                break;
            case '\"':  // Gestione delle virgolette doppie
                if (!in_single_quotes) {
                    in_double_quotes ^= 1;
                    continue;  // Non includere le virgolette doppie nel risultato finale
                }
                break;
            case '$':  // Espansione delle variabili
                if (!in_single_quotes && (isalnum(value[i + 1]) || value[i + 1] == '_')) {
                    char var_name[256];
                    int var_len = 0;
                    i++;
                    while (isalnum(value[i]) || value[i] == '_') {
                        var_name[var_len++] = value[i++];
                    }
                    var_name[var_len] = '\0';
                    char *var_value = getenv(var_name);
                    if (var_value) {
                        strcpy(result + out_index, var_value);
                        out_index += strlen(var_value);
                    }
                    i--;  // Regolazione dell'indice dopo l'espansione
                    continue;
                }
                break;
        }
        result[out_index++] = value[i];
    }
    result[out_index] = '\0';
    return result;
}

// Espande i tokens nell'elenco
t_list *expand(t_list **list) {
    t_list *current = *list;
    while (current) {
        t_token *token = current->content;
        if (token->type == TOKEN_WORD) {
            char *new_value = expand_token_value(token->value);
            free(token->value);
            token->value = new_value;
        }
        current = current->next;
    }
    return *list;
}
