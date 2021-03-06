/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dburtnja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 18:34:41 by dburtnja          #+#    #+#             */
/*   Updated: 2017/07/03 18:34:42 by dburtnja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			get_nbr_after_flag(char **argv, int argc, int *i)
{
	int	error;
	int ret_val;

	(*i)++;
	if (*i >= argc)
		ft_error(ft_strjoin("No parameter after flag ", argv[(*i) - 1]));
	ret_val = ft_atoi_move(&(argv[*i]), &error, FALSE);
	if (error == TRUE || ret_val <= 0)
		ft_error(ft_strjoin("Bad number: ", argv[*i]));
	return (ret_val);
}

void		read_flags(t_vm *main_struct, char **argv, int argc, int *i)
{
	if (ft_strcmp("-dump", argv[*i]) == 0)
	{
		main_struct->dump_cycle = get_nbr_after_flag(argv, argc, i);
		main_struct->f_dump = TRUE;
	}
	else if (ft_strcmp("-v", argv[*i]) == 0)
		main_struct->f_v = TRUE;
	else if (ft_strcmp("-log", argv[*i]) == 0)
		main_struct->f_log = TRUE;
	else if (ft_strcmp("-aff", argv[*i]) == 0)
		main_struct->f_aff = TRUE;
	else if (ft_strcmp("-alive", argv[*i]) == 0)
		main_struct->f_alive = TRUE;
	else if (ft_strcmp("-usage", argv[*i]) == 0)
		usage();
	else
		ft_error(ft_strjoin("NO such flag - ", argv[*i]));
}

t_player	*add_players(t_vm *main_struct, char **argv, int argc, int *i)
{
	int boot_nbr;

	boot_nbr = 0;
	(main_struct->players_nbr)++;
	if (main_struct->players_nbr > MAX_PLAYERS)
		ft_error(ft_strjoin("To many players, allowed - ",
							ft_itoa(MAX_PLAYERS)));
	if (ft_strcmp("-n", argv[*i]) == 0)
	{
		boot_nbr = get_nbr_after_flag(argv, argc, i);
		(*i)++;
		if (*i >= argc)
			ft_error("No file after -n N");
	}
	return (create_players(argv[*i], boot_nbr));
}

void		check_if_name_is_valid(t_vm *main_struct)
{
	int i;
	int	j;
	int bul_same_name;
	int bul_same_players;

	i = 0;
	while (main_struct->players_nbr > i)
	{
		j = 0;
		while (main_struct->players_nbr > j)
		{
			bul_same_name = main_struct->players[i]->name ==
					main_struct->players[j]->name;
			bul_same_players = main_struct->players[i] ==
					main_struct->players[j];
			if (bul_same_name && !bul_same_players)
				ft_error(ft_strjoin("Players have identical names = ",
				ft_itoa(main_struct->players[i]->name)));
			j++;
		}
		i++;
	}
}

void		read_arguments(t_vm *main_struct, char **argv, int argc)
{
	int			i;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '-' && argv[i][1] != 'n')
			read_flags(main_struct, argv, argc, &i);
		else
			main_struct->players[main_struct->players_nbr - 1] =
					add_players(main_struct, argv, argc, &i);
		i++;
	}
	create_names_players(main_struct);
	check_if_name_is_valid(main_struct);
}
