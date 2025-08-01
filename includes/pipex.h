/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 02:47:05 by ybelghad          #+#    #+#             */
/*   Updated: 2025/07/21 02:50:32 by ybelghad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./types.h"

//--------------------°°manage_pipex_fds°°--------------//
void		setup_input(int p);
void		setup_output(int *fd, int i, int ac);
void		close_pr_fds(t_script *script, int *p, int *fd);

//------------------°°wait_exit°°-----------//
void		ft_perror(char *str, int ex_st);
void	printerror(t_minishell *minishell, char **args, char *err, int exinum);
int			wait_for_children(int *pid, int ac);

#endif // !PIPEX_H
