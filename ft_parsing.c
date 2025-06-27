/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:14:27 by ybelghad          #+#    #+#             */
/*   Updated: 2025/06/12 18:14:27 by ybelghad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int nb_cmds(char *str)
{
    int nb;

    nb = 0;
    while (*str)
    {
        if (*str == '|')
            nb++;
        str++;
    }
    return (nb);
}

int main()
{
    printf("%d\n", nb_cmds("<< del cat -e | grep hippo | tr 'p' 's' | cat | wc -l > out.txt"));
}

/*char	**ft_parsing(t_script *script)
{
}*/

