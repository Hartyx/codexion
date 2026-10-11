/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safidyan <safidyan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 05:40:08 by safidyan          #+#    #+#             */
/*   Updated: 2026/10/05 00:27:44 by safidyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


static int  parse_num(char *s)
{
    long    n;
    int i;


    i = 0;
    if (!s || s[0] == '\0')
        return (0);
    if (s[i] == '+')
        i++;
    if (s[i] == '\0')
        return (0);
    n = 0;
    while (s[i])
    {
        if (s[i] < '0' || s[i] > '9')
            return (0);
        n = n * 10 + (s[i] - '0');
        if (n > INT_MAX)
            return (0);
        i++;
    }
    return (1);
}


static int set_scheduler(char *s, t_config *cfg)
{
    if (strcmp(s, "fifo") == 0)
        cfg -> use_edf = 0;
    else if (strcmp(s, "edf") == 0)
        cfg -> use_edf = 1;
    else
        return (1);
    return (0);
}

static void fill_config(long *v, t_config *cfg)
{
    cfg -> nb_coders = (int)v[0];
    cfg -> time_to_burnout = v[1];
    cfg -> time_to_compile = v[2];
    cfg -> time_to_debug = v[3];
    cfg -> time_to_refactor = v[4];
    cfg -> nb_compiles_required = (int)v[5];
    cfg -> dongle_cooldown = v[6];
}

static int	print_error(char *msg)
{
	fprintf(stderr, "Error: %s\n", msg);
	return (1);
}

int	parse_args(int argc, char **argv, t_config *cfg)
{
	long	v[7];
	int		i;

	if (argc != 9)
	{
		fprintf(stderr, "Usage: %s coders burnout compile debug refactor "
			"compiles_required cooldown fifo|edf\n", argv[0]);
		return (1);
	}
	i = 0;
	while (i < 7)
	{
		if (!parse_num(argv[i + 1]))
            return (print_error("invalid number"));
        v[i] = atoi(argv[i + 1]);
		i++;
	}
	if (v[0] < 1 || set_scheduler(argv[8], cfg))
		return (fprintf(stderr, "Error: bad coders or scheduler\n"), 1);
	fill_config(v, cfg);
	return (0);
}

