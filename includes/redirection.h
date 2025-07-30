/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 23:14:47 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/07/30 23:14:59 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "./types.h"

int		save_fds(t_red *red);
void	restore_fds(t_red *red);
int		apply_redirection(t_red *current);
void	redirect_io(t_red *current);
int		redirection(t_red *red);

#endif
