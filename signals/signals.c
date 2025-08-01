/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 01:30:59 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/08/01 01:57:19 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/signals.h"
#include <signal.h>

volatile sig_atomic_t g_received_signal = 0;





