/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamza <ehamza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:44:00 by ehamza            #+#    #+#             */
/*   Updated: 2025/07/12 14:44:01 by ehamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void expander(char **str)
{
    char *dolar;
    int i = 0;

    dolar = ft_strchr(*str, '$');
    while (dolar != NULL)
    {
        while(dolar[i] != ' ')
        {
            dolar[i] =  'A';
            i++;
        }
        dolar = ft_strchr(*str, '$');
    }
}

int main()
{
    char *str = ft_strdup("cdschsdc$HOME clkdsc $KFD :DFFDKFDF");
    expander(&str);
    printf("%s\n", str);
}
