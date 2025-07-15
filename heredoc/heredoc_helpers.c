#include "../includes/heredoc.h"

heredoc_t	*init_heredoc(void)
{
    heredoc_t	*new;

    new = malloc(sizeof(heredoc_t));
    if (!new)
        return (perror("malloc"), NULL);
    new->fd = -1;
    new->tmp_fd = -1;
    new->filename = NULL;
    new->line = NULL;
    new->del = NULL;
    return (new);
}
