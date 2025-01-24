#include "../minishell.h"
#include "builtin/builtin.h"
#include <stdio.h>
#include <string.h>

char	*ft_strjoin_char(char *s1, char c)
{
    char	*result;
    size_t	len;

    len = ft_strlen(s1);
    result = ft_calloc(sizeof(char) , len + 2);
    if (!result)
		return (NULL);
	memcpy(result, s1, len);
    result[len] = c;
    result[len + 1] = '\0';
    return (result);
}

char	*expand_var(char *var, char **env)
{
    int		start;
    char	*ret;
    char	c;

    start = 0;
    while ((ft_isalnum(var[start]) && var[start] == '?') || var[start] == '_')
        start++;
    c = var[start];
    var[start] = '\0';
    if (*var == '?')
        ret = ft_itoa(g_status);
    else
	{
		if (get_env(env, var))
        	ret = ft_strdup(get_env(env, var));
		else
		 return ft_strdup("");
	}
    var[start] = c;
    return (ret);
}	

int	var_len(char *var)
{
    int		start;

    start = 0;
    while ((ft_isalnum(var[start]) && var[start] == '?') || var[start] == '_')
        start++;
    return (start);
}

char	*remove_quotes(char *str)
{
    char	*result;
    int		i, j;
    char	in_single_quote = 0;
    char	in_double_quote = 0;

    result = malloc(ft_strlen(str) + 1);
    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] == '\'')
            in_single_quote = !in_single_quote;
        else if (str[i] == '"' && !in_single_quote)
            in_double_quote = !in_double_quote;
        else
            result[j++] = str[i];
        i++;
    }
    result[j] = '\0';
    return (result);
}

char	*expand_token(char *str, char **env)
{
    char	*tmp;
    char	*swp;
    char	*ret;
    char	in_single_quote = 0;
    char	in_double_quote = 0;

    ret = ft_strdup("");
    while (*str)
    {
        if (*str == '\'')
            in_single_quote = !in_single_quote;
        else if (*str == '"' && !in_single_quote)
            in_double_quote = !in_double_quote;
        else if (*str == '$' && !in_single_quote)
        {
            str++;
            tmp = expand_var(str, env);
            str += var_len(str);
            swp = ret;
            ret = ft_strjoin(ret, tmp);
            free(tmp);
            free(swp);
            continue;
        }
        else
        {
            swp = ret;
            ret = ft_strjoin_char(ret, *str);
            free(swp);
        }
        str++;
    }
    char *no_quotes = remove_quotes(ret);
    free(ret);
    return no_quotes;
}
