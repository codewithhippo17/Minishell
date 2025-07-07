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
#include <signal.h>

static void run_heredoc_child(heredoc_t *hd)
{
    signal(SIGINT, SIG_DFL);
    hd->fd = open(hd->filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
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
        return (-1);
    else if (WIFEXITED(hd->status) && WEXITSTATUS(hd->status) != 0)
        return (perror("open tmp for reading"), -1);
    hd->fd = open(hd->filename, O_RDONLY);
    if (hd->fd < 0)
        return (perror("open tmp for reading"), -1);
    return (0);
}

void handle_sigint(int sig)
{
    (void)sig;
    printf("\n");
    if (g_heredoc)
        free_heredoc(g_heredoc);
    exit(128 + SIGINT);
}

int heredoc(heredoc_t *hd)
{
    signal(SIGINT, handle_sigint);
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

/*int main(int argc, char **argv)
{
    heredoc_t *hd;
    char *random_str;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <delimiter>\n", argv[0]);
        return EXIT_FAILURE;
    }

    hd = init_heredoc();
    if (!hd)
        return EXIT_FAILURE;
    
    g_heredoc = hd;  // Set global for signal handler

    random_str = ft_random();
    if (!random_str)
        return free_heredoc(hd), EXIT_FAILURE;
    
    hd->filename = ft_strjoin("/tmp/heredoc_", random_str);
    free(random_str);
    if (!hd->filename)
        return free_heredoc(hd), EXIT_FAILURE;

    hd->del = ft_strdup(argv[1]);
    printf("Delimiter: %s\n", hd->del);
    if (!hd->del)
        return free_heredoc(hd), EXIT_FAILURE;

    if (heredoc(hd) < 0)
        return free_heredoc(hd), EXIT_FAILURE;

    // Do something with hd->fd...

    g_heredoc = NULL;  // Clear global before cleanup
    free_heredoc(hd);
    return EXIT_SUCCESS;
}
*/
