/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultins.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 20:16:11 by ybelghad          #+#    #+#             */
/*   Updated: 2025/07/11 20:16:11 by ybelghad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BULTINS_H

# define BULTINS_H
# include "./types.h"

//----------------ººbuild-in_cmd_utilsºº------------------//

int			echo(char **s);
int			cd(char **str, t_minishell *minishell);
int			pwd(void);
int			envierment(char **m_env);
int			ft_my_exit(t_minishell *minishell);
int			update_variable(char *s, char **env, int i);
int			exports(char *var, char ***env);
int			exec_export(t_minishell *minishell);
int			unset_env(char *var, char ***env);
int			exec_unset(t_minishell *minishell);

#endif
