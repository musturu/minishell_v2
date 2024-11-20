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

char	*expand(char *str, char **env, int count)
{
	char	*ret;
	char	*first;
	char	*next;
	char	*last;
	int		i;


	i = 0;
	if (ft_strchr(str, '"'))
	{
		ret = ft_strdupdb(str);
		printf("ret1 = %s\n", ret);
	}
	while (ret[i])
	{
		if (ret[i] == '$')
		{
			first = ft_substr(ret, 0, i);
			printf("first = %s\n", first);
			count++;
			printf("count = %d\n", count);
			break;
		}
		i++;
	}
	if (count == 1)
	{
		first = ft_strdup((env[str_to_env_index(env, first)] + (ft_strlen(first) + 1)));
		printf("first1 = %s\n", first);
		next = ft_substr(ret, i, ft_strlen(ret));
		printf("next1 = %s\n", next);
		ret = ft_strjoin(first, next);
		printf("ret1 = %s\n", ret);
	}
	else if (count > 1)
	{
		next = ft_substr(ret, i + 1, ft_strlen(ret));
		printf("next2 = %s\n", next);
		i = 0;
		while (next[i])
		{
			if (next[i] == '$' || next[i] == ' ')
			{
				next = ft_substr(next, 0, i);
				printf("next22 = %s\n", next);
				last = ft_substr(ret, i, ft_strlen(ret));
				break;
			}
			i++;
		}
		next = ft_strdup((env[str_to_env_index(env, next)] + (ft_strlen(next) + 1)));
		printf("next222 = %s\n", next);
		next = ft_strjoin(next, last);
		ret = ft_strjoin(first, next);
	}
	else if (count == 0)
		ret = ft_strdup((env[str_to_env_index(env, ret)] + (ft_strlen(ret) + 1)));
	count++;
	printf("count = %d\n", count);
	return (ret);
}


char	*dquote_manager(char *str, char **env)
{
	int		i;
	char	*first;
	char	*ret;
	char	*second;
	static int		count;

	count = 0;
	i = 1;
	if (!count_quotes(str, '\"'))
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '$')
			break ;
		i++;
	}
	first = (ft_substr(str, 1, i - 1));
	printf("first1 = %s\n", first);
	if (ft_strchr(str, '$'))
	{
		second = expand((ft_strchr(str, '$') + 1), env, count);
		printf("second = %s\n", second);
		while (ft_strchr(second, '$'))
			second = expand((ft_strchr(second, '$') + 1), env, count);
	}
	while (!ft_isspace(str[i]))
		i++;
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
	while (!ft_isspace(str[i]))
		i++;
	second = ft_substr(str, 0, i - 1);
	ret = ft_strjoin(first, second);
	free(first);
	free(second);
	return (ret);
}
