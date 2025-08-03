/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 23:14:47 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/08/02 16:48:29 by ybelghad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "./types.h"

int	save_fds(t_script *script);
int	restore_fds(t_script *script);
int	apply_redirection(t_red *current);
int	redirect_io(t_red *current);
int	redirection(t_script *script);

#endif
