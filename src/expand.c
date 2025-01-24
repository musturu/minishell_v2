#include "../minishell.h"

char	*expand_var(char *var, char **env)
{
    int		start;
	char	*ret;
	char	c;

    start = 0;
    while (ft_isalnum(var[start]) || var[start] == '_')
		start++;
	c = var[start];
	var[start] = '\0';
	if (*var == '?')
		ret =(ft_itoa(g_status));
	ret = (ft_strdup(get_env(env, var)));
	var[start] = c;
	return (ret);
}	

int	var_len(char *var)
{
    int		start;

    start = 0;
    while (ft_isalnum(var[start]) || var[start] == '_')
		start++;
	return (start);
}

char	*expand_token(char *str, char **env)
{
	char	*first;
	char	*tmp;
	char	*swp;
	char	*ret;

	tmp = ft_strchr(str, '$');
	if (!tmp)
		return (ft_strdup(str));
	first = ft_substr(str, 0, tmp - str);
	ret = ft_strjoin(first, "");
	str = str + ft_strlen(first);
	free(first);
	while (tmp)
	{
		str = str + var_len(tmp + 1);
		tmp = expand_var(tmp + 1, env);
		swp = ret;
		ret = ft_strjoin(ret, tmp);
		free(tmp);
		free(swp);
		tmp = ft_strchr(str, '$');
	}
	return (ret);
}
