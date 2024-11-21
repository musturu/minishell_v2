#include "../minishell.h"
#include <stdio.h>

t_list *expand(t_list **list, char **env)
{
    printf("EXPANDER\n");
    t_list *tmp = *list;
    token *tkn;

    while (tmp)
    {
        tkn = tmp->content;
        printf("%s - %i\n", tkn->value, tkn->type);

        if (tkn->type == TOKEN_DOLLAR)
        {
            printf("%s - %i\n", tkn->value, tkn->type);
            if (strchr(tkn->value + 1, '$'))
            {
                char *original = tkn->value;
                char *result = malloc(1);
                *result = '\0';

                char *next_part = original;
                char *start;
                while ((start = strchr(next_part, '$')))
                {
                    char *end = start + 1;
                    while (*end && *end != '$' && !isspace(*end)) end++;

                    char saved = *end;
                    *end = '\0';
					printf("start: %s\n", start);
                    char *env_value = ft_strdup((env[str_to_env_index(env, start + 1)] + ft_strlen(start)));
					printf("env_value: %s\n", env_value);
                    *end = saved;

                    result = realloc(result, strlen(result) + strlen(env_value) + (start - next_part) + 1);
                    strncat(result, next_part, start - next_part);
                    strcat(result, env_value);

                    next_part = end;
                }
                strcat(result, next_part);
                free(original);
                tkn->value = result;
                tkn->type = TOKEN_WORD;
            }
            else if (ft_strlen(tkn->value) == 1)
            {
                tkn->value = ft_strdup("$");
                tkn->type = TOKEN_WORD;
            }
            else
            {
				if (str_to_env_index(env, tkn->value + 1) == -1)
				{
					tkn->value = ft_strdup("");
					tkn->type = TOKEN_WORD;
				}
				else
				{
					tkn->value = ft_strdup((env[str_to_env_index(env, tkn->value + 1)] + ft_strlen(tkn->value) + 1));
					tkn->type = TOKEN_WORD;
				}
            }
        }
        tmp = tmp->next;
    }
    return (*list);
}
