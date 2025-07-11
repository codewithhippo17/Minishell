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
    new->next = NULL;
    new->line = NULL;
    new->del = NULL;
    return (new);
}

void	free_heredoc(heredoc_t *hd)
{
    if (hd)
    {
        if (hd->filename)
            free(hd->filename);
        if (hd->line)
            free(hd->line);
        if (hd->del)
            free(hd->del);
        if (hd->fd >= 0)
            close(hd->fd);
        hd->prev = hd->next;
        hd->next = NULL;
        free(hd);
    }
}

void	free_heredoc_list(heredoc_t *hd)
{
    heredoc_t	*tmp;

    while (hd)
    {
        tmp = hd;
        hd = hd->next;
        free_heredoc(tmp);
    }
}

void add_heredoc(heredoc_t **head, heredoc_t *new)
{
    if (!head || !new)
        return;
    new->next = *head;
    *head = new;
}
