/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 03:22:08 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/07/22 03:22:08 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char **s)
{
	if (ft_strcmp(s[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(s[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(s[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(s[0], "env") == 0)
		return (1);
	else if (ft_strcmp(s[0], "export") == 0)
		return (1);
	else if (ft_strcmp(s[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(s[0], "exit") == 0)
		return (1);
	return (0);
}

int	is_piped(char *input)
{
	if (ft_strchr(input, '|'))
		return (1);
	return (0);
}
