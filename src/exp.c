#include "../minishell.h"
#include <stdio.h>

char	*getwordvalue(char **str, char **ret)
{
	char	*tmp;
	char	*load;

	if (*ret == NULL)
		*ret = ft_strdup("");
	tmp = *ret;
	if (*ret && !ft_istokenquotes(**str) && (!**str || ft_istokenchar(**str) || ft_isspace(**str)))
	{
		tmp = ft_strdup(*ret);
		free(*ret);
		return tmp;
	}
	if (**str != '"' && **str != '\'')
		load = ft_substr(*str, 0, space_until_next(*str));
	else
		if (ft_strchr(*str, **str))
			load = ft_substr(*str, 0, ft_strchr(*str + 1, **str) - *str  );
		else
		 return NULL;
	*ret = ft_strjoin(*ret, load);
	*str += ft_strlen(load);
	free(tmp);
	free(load);
	return (getwordvalue(str, ret));
}
