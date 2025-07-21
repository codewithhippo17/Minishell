/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 00:07:32 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/07/22 00:07:32 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool is_joinable(t_token *c)
{
    if (!c->next)
        return (true);
    if ((c->join == J || c->join == JR) && (c->next->join == JL || c->next->join == J))
        return (true);
    return (false);
}

// here a function that flag ambg for the splited
// if there is more than one token in the splited tokens && they can not be joined
// based on the join flag
// it will set the ambg flag to AMBG in all the tokens int the splited tokens
// join flag is set to NONE or NJ


void flag_ambg(t_token *token)
{
    t_token *c;
    bool    is_ambg;

    is_ambg = false;
    c = token;
    if (!c)
        return ;
    while (c && is_ambg == false)
    {
        if (is_joinable(c) == false)
            is_ambg = true;
        c = c->next;
    }
    if (is_ambg == true)
    {
        c = token;
        while (c)
        {
            c->ambg = AMBG;
            c = c->next;
        }
    }
}

