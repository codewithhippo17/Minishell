/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 20:30:58 by ybelghad          #+#    #+#             */
/*   Updated: 2025/07/15 10:55:33 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KILL_H
# define KILL_H

# include "types.h"

//---------------ººfree_exitºº-----------------//
void	free_strings(char **s);
void	ft_close_wait_exit(int p_fd[], int pid1, int pid2);
void	free_exit_minishell(t_minishell *minishell, int status);

#endif
