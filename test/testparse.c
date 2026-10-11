#include "codexion.h"

// parse_num : transforme une chaîne en nombre, en refusant tout ce qui est invalide.
// set_scheduler : accepte seulement fifo ou edf.
// fill_config : range les valeurs dans la struct.
// parse_args : vérifie argc, appelle les autres et retourne 0 (OK) ou 1 (erreur).

static int	parse_num(char *s, long *out)
{
	long	n;
	int		i;

	i = 0;
	if (s[i] == '+')
		i++;
	if (s[i] == '\0')
		return (1);
	n = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (1);
		n = n * 10 + (s[i] - '0');
		if (n > INT_MAX)
			return (1);
		i++;
	}
	*out = n;
	return (0);
}

static int	set_scheduler(char *s, t_config *cfg)
{
	if (strcmp(s, "fifo") == 0)
		cfg->use_edf = 0;
	else if (strcmp(s, "edf") == 0)
		cfg->use_edf = 1;
	else
		return (1);
	return (0);
}

static void	fill_config(long *v, t_config *cfg)
{
	cfg->nb_coders = (int)v[0];
	cfg->time_to_burnout = v[1];
	cfg->time_to_compile = v[2];
	cfg->time_to_debug = v[3];
	cfg->time_to_refactor = v[4];
	cfg->nb_compiles_required = (int)v[5];
	cfg->dongle_cooldown = v[6];
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
		if (parse_num(argv[i + 1], &v[i]))
			return (fprintf(stderr, "Error: invalid number '%s'\n",
					argv[i + 1]), 1);
		i++;
	}
	if (v[0] < 1 || set_scheduler(argv[8], cfg))
		return (fprintf(stderr, "Error: bad coders or scheduler\n"), 1);
	fill_config(v, cfg);
	return (0);
}