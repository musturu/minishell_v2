#include "../minishell.h"
#include <stdio.h>

int	count_quotes(char *str, char quote)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	while(str[i])
	{
		if (str[i] == quote)
			ret++;
		i++;
	}
	if (ret % 2 == 1)
		return (0);
	else
		return (1);
}

char	*ft_strdupdb(char *str)
{
	int		strlen;
	char	*res;
	int		i;

	strlen = 0;
	while (str[strlen])
		strlen++;
	i = 0;
	res = (char *)malloc(sizeof(char) * strlen + 1);
	if (res == NULL)
		return (NULL);
	while (str[i])
	{
		if(str[i] != '"')
			res[i] = str[i];
		else
			break;
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*dquote_manager(char *str, char **env)
{
		int		i;
	char	*first;
	char	*ret;
	char	*second;

	i = 1;
	if (!count_quotes(str, '"'))
		return (NULL);
	while (str[i])
	{
		if (str[i] == '"')
			break ;
		i++;
	}
	second = (ft_substr(str, 1, i - 1));
	first = handle_quoted_expansion(second, env);
	free(second);
	str += i + 1;
	if (isspace(str[0]))
		return (first);
	second = ft_substr(str, 0, i - 1);
	ret = ft_strjoin(first, second);
	free(first);
	free(second);
	return (ret);
}
char	*squote_manager(char *str)
{
	int		i;
	char	*first;
	char	*ret;
	char	*second;

	i = 1;
	if (!count_quotes(str, '\''))
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'')
			break ;
		i++;
	}
	first = (ft_substr(str, 1, i - 1));
	str += i + 1;
	if (isspace(str[i]))
		return (first);
	second = ft_substr(str, 0, i - 1);
	ret = ft_strjoin(first, second);
	free(first);
	free(second);
	return (ret);
}

char	*word_manager(char *str, char **env)
{
	int		i;
	char	*first;
	char	*ret;
	char	*second;

	i = 0;
	while (str[i])
	{
		if (ft_istokenchar(str[i]) && (str[i] != '"' || str[i] != '\''))
			break ;
		if (str[i] == '"' || str[i] == '\'')
		{
			first = ft_substr(str, 0, i);
			if (str[i] == '"')
				second = dquote_manager(str+i, env);
			else
				second = squote_manager(str+i);
			ret = (ft_strjoin(first, second));
			free(first);
			free(second);
			return (ret);
		}
		i++;
	}
	return ft_substr(str, 0, space_until_next(str)) ;
}
