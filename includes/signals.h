/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 01:30:06 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/08/01 01:53:16 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

extern sig_atomic_t	g_received_signal;

void						setup_shell_signals(void);
void						setup_child_signals(void);
void						restore_shell_signals(void);
void						setup_ignore_signals(void);

#endif
