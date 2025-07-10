/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamza <ehamza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 22:59:00 by ehamza            #+#    #+#             */
/*   Updated: 2025/07/06 22:59:01 by ehamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/heredoc.h"
#include "../minishell.h"
#include <stdio.h>
#include <unistd.h>

static void run_heredoc_child(heredoc_t *hd)
{
    signal(SIGINT, SIG_DFL);
    hd->fd = open(hd->filename, O_CREAT | O_WRONLY | O_TRUNC, 0444);
    if (hd->fd < 0)
    {
        perror("open tmp");
        free(hd->filename);
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        hd->line = readline("> ");
        if (!hd->line || strcmp(hd->line, hd->del) == 0)
            break;
        write(hd->fd, hd->line, ft_strlen(hd->line));
        write(hd->fd, "\n", 1);
        free(hd->line);
    }
    free(hd->line);
    close(hd->fd);
    free(hd->filename);
    free(hd->del);
    exit(EXIT_SUCCESS);
}

static int run_heredoc_parent(heredoc_t *hd)
{
    waitpid(hd->pid, &hd->status, 0);
    if (WIFSIGNALED(hd->status))
        return (perror("heredoc child terminated by signal"), -1);
    else if (WIFSTOPPED(hd->status))
        return (perror("heredoc child stopped"), -1);
    else if (WIFEXITED(hd->status) && WEXITSTATUS(hd->status) != 0)
        return (perror("open tmp for reading"), -1);
    hd->fd = open(hd->filename, O_RDONLY);
    if (hd->fd < 0)
        return (perror("open tmp for reading"), -1);
    unlink(hd->filename);
    return (0);
}


int heredoc(heredoc_t *hd)
{ 
    hd->pid = fork();
    if (hd->pid < 0)
    {
        perror("fork");
        return -1;
    }
    if (hd->pid == 0)
        run_heredoc_child(hd);
    return (run_heredoc_parent(hd));
}
