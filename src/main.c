/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safidyan <safidyan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 07:56:12 by safidyan          #+#    #+#             */
/*   Updated: 2026/10/19 15:45:48 by safidyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_config	cfg;
	t_data		data;
	int			ret;

	if (parse_args(argc, argv, &cfg))
		return (1);
	if (init_data(&data, &cfg))
		return (1);
	ret = start_simulation(&data);
	cleanup(&data);
	return (ret);
}
