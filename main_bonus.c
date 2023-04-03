/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 14:55:08 by msoria-j          #+#    #+#             */
/*   Updated: 2023/04/03 11:58:23 by msoria-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex_bonus.h"

void	here_doc(char *outfile, char *limiter)
{
	int		fd;
	int		i, j;
	char	*buffer;
	
	buffer = ft_calloc(1, 1000 * sizeof(buffer));
	ft_fprintf(2, "Limiter: %s\n", limiter);
	fd = open(outfile, O_RDWR | O_CREAT | O_APPEND);
	i = -1;
	j = 0;
	while (++i < 1000)
	{
		read(STDIN_FILENO, buffer, 1);
		if (*buffer == '\n')
		{
			buffer++;
			i++;
			j += i;
			if (ft_strnstr(buffer - i, limiter, ft_strlen(limiter)))
				break ;
			else
			{
				// ft_fprintf(fd, "%s", buffer - j); // cambiar por execve
				i = -1;
				/* free(buffer);
				buffer = ft_calloc(1, 1000 * sizeof(buffer)); */
			}
		}
		else
			buffer++;
	}
	// ft_fprintf(2, "j - i: %d\n%s\n", j - i, buffer - j);
	buffer -= j;
	buffer[j - i] = '\0';
	ft_fprintf(fd, "%s\n", buffer);
	
	free(buffer);
	close(fd);
	exit(0);
}

/* Check the argument number */
static void	check_argc(int argc, char **argv)
{
	if (ft_strnstr(argv[1], "here_doc", 8))
		// ft_fprintf(2, "here_doc\n");
		here_doc(argv[argc - 1], argv[2]);
	if (argc < 5)
	{
		errno = EINVAL;
		perror("Error");
		exit(errno);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_descriptors	d;
	t_paths			p;
	int				i;

	check_argc(argc, argv);
	p.argv = argv;
	p.envp = envp;
	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	p.paths = ft_split(envp[i] + 5, ':');
	pipe(d.pipe_fd);
	d.fork_id = fork();
	waitpid(d.fork_id, &i, WNOHANG);
	if (d.fork_id == 0)
		exec_child(d, &p);
	else
		exec_parent(d, &p);
	free_structs(&p, FREE_ALL);
	return (EXIT_SUCCESS);
}
