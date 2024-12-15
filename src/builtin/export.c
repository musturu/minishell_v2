#include    "../../minishell.h"

int	already_present(char    *str, char    **env)
{
    int i;
    int len;
    char    *eq;

    i = -1;
    len = ft_strlen(str);
    eq = ft_strchr(str, '=');
    if (eq != NULL)
        len = eq - str - 1;
    while (env[++i])
    {
        if (!ft_strncmp(str , env[i], len - 1))
            return (i);
    }
    return (-1);
}

void    matrixdup(char  ***dst, char ***src)
{
    int i;

    i = 0;
    if (!*src)
    {
        *dst = NULL;
        return ;
    }
    while ((*src)[i])
    {
        (*dst)[i] = ft_strdup((*src)[i]);
        //free(*src[i]); DECOMMENTARE QUANDO COPIO ENV ALLINIZIO DEL PROGRAMMA
        i++;
    }
    //free(*src);
    src = dst;
}

void    update_exp(char *str, char    ***env)
{
    char    *eq;
    int     i;

    eq = ft_strchr(str, '=');
    if (!eq)
        return ;
    if (eq != NULL)
    {
        i = already_present(str, *env);
        free((*env)[i]);
        (*env)[i] = ft_strdup(str);
    }
}

void    insert_exp(char *str, char    ***env)
{
    char    *tmp;
    char    *nulstr;
    char    **envcpy;
    int i;

    i = 0;
    while ((*env)[i])
        i++;
    envcpy = ft_calloc(i + 2, sizeof(char **));
    matrixdup(&envcpy, env);
    if (ft_strchr(str, '='))
    {
        (*env)[i] = ft_strdup(str);
        (*env)[i + 1] = NULL;
    }
    else
    {
        tmp = ft_strdup(str);
        nulstr = ft_strjoin(str, "=\'\'");
        (*env)[i] = nulstr;
        (*env)[i + 1] = NULL;
        free(tmp);
    }
}

int export(char **argv, char ***en)
{
    int i;

    i = 0;
    if (!argv[1])
        return env(*en);
    while (argv[++i])
    {
        if (already_present(argv[i], *en))
            update_exp(argv[i], en);
        else
            insert_exp(argv[i], en);
    }
    return (0);
}
