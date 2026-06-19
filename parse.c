#include "ft_ls.h"

void	parse_ft_ls_options(t_ls *ls, int argc, char **argv)
{
	int				i;
	int				j;
	int				len;
	struct stat		check_stat;

	i = 1;

	while (i < argc)
	{
		if (argv[i][0] == '-' && ft_strlen(argv[i]) > 1)
		{
			j = 1;
			while (argv[i][j])
			{
				if (argv[i][j] == 'l' || argv[i][j] == 'a' ||
					argv[i][j] == 't' || argv[i][j] == 'r' ||
					argv[i][j] == 'R')
				{
					if (!ft_strchr(ls->options, argv[i][j]))
					{
						len = ft_strlen(ls->options);
						ls->options[len] = argv[i][j];
						ls->options[len + 1] = '\0';
					}
				}
				else
				{
					write(2, "ft_ls: illegal option\n", 22);
					exit(EXIT_FAILURE);
				}
				j++;
			}
		}
		else
		{
			if (lstat(argv[i], &check_stat) == -1)
			{
				write(2, "ft_ls: cannot access '", 22);
				write(2, argv[i], ft_strlen(argv[i]));
				write(2, "': ", 3);
				ft_putstr_endl(strerror(errno));
				exit(EXIT_FAILURE);
			}

			ls->paths[ls->path_count] = argv[i];
			ls->path_count++;
		}
		i++;
	}

	if (ls->path_count == 0)
	{
		ls->paths[0] = ".";
		ls->path_count = 1;
	}
}