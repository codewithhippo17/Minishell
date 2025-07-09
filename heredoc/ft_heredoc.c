#include "../includes/heredoc.h"
#include "../minishell.h"

void ft_heredoc(t_token *token, char *delimiter)
{
    heredoc_t *hd;
    int result;

    hd = init_heredoc();
    if (!hd)
        return ;
    hd->del = ft_strdup(delimiter);
    if (!hd->del)
    {
        free_heredoc(hd);
        return ;
    }
    hd->filename = ft_strjoin("/tmp/", ft_random());
    if (!hd->filename)
    {
        free_heredoc(hd);
        return ;
    }
    result = heredoc(hd);
    if (result == -1)
    {
        free_heredoc(hd);
        return ;
    }
    token->hd = hd;  // Store in token, not global
}



