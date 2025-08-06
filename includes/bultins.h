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

int	echo(char **s);
int	cd(char **str, t_minishell *minishell);
int	pwd(void);
int	envierment(char **m_env);
int	ft_my_exit(t_script *script);
int	update_variable(char *s, char **env, int i);
int	exports(char *var, char ***env);
int	exec_export(t_minishell *minishell, t_script *script);
int	unset_env(char *var, char ***env);
int	exec_unset(t_minishell *minishell, t_script *script);
int	builtin_echo(t_minishell *m, t_script *s);
int	builtin_cd(t_minishell *m, t_script *s);
int	builtin_pwd(t_minishell *m, t_script *s);
int	builtin_env(t_minishell *m, t_script *s);
int	builtin_export(t_minishell *m, t_script *s);
int	builtin_unset(t_minishell *m, t_script *s);
int	builtin_exit(t_minishell *m, t_script *s);
int	builtin_unknown(t_minishell *m, t_script *s);
int	execute_builtin(t_minishell *minishell, t_script *script, t_builtin_name name);
t_builtin_name which_bultin(const char *cmd);

#endif
