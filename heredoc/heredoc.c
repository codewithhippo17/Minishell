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
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

static void expander(char **str)
{
    char *dolar;
    char 
    int i = 0;

    dolar = ft_strchr(*str, '$');
    while (dolar != NULL)
    {
        while(dolar[i] != ' ')
        {
            dolar[i] =  'A';
            i++;
        }
        dolar = ft_strchr(*str, '$');
    }
}

int main()
{
    char *str = ft_strdup("cdschsdc$HOME clkdsc $KFD :DFFDKFDF");
    expander(&str);
    printf("%s\n", str);
}
/*
static void run_heredoc_child(heredoc_t *hd)
{
    signal(SIGINT, SIG_DFL);
    while (1)
    {
        hd->line = readline("> ");
        if (!hd->line || strcmp(hd->line, hd->del) == 0)
            break;
        write(hd->tmp_fd, hd->line, ft_strlen(hd->line));
        write(hd->tmp_fd, "\n", 1);
        free(hd->line);
    }
    free(hd->line);
    close(hd->tmp_fd);
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
    return (0);
}


int heredoc(heredoc_t *hd)
{
    hd->tmp_fd = open(hd->filename, O_CREAT | O_WRONLY , 0600);
    hd->fd = open(hd->filename, O_RDONLY, 0600);
    unlink(hd->filename);
    hd->pid = fork();
    if (hd->pid < 0)
    {
        perror("fork");
        return -1;
    }
    if (hd->pid == 0)
        run_heredoc_child(hd);
    else
        run_heredoc_parent(hd);
    return (0);
}*/
