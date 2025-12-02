/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 02:13:45 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/02 06:53:58 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	error_exit(char **path, char *str, int errno)
{
	free_path(path);
	perror(str);
	exit(errno);
}

//void	wait_exit(pid_t pid[], t_pipe info)
//{
//	int	i;
//	int	tmp;
//	int	status;

//	status = 0;
//	tmp = 0;
//	i = FIRST;
//	while (i <= info.LAST)
//	{
//		waitpid(pid[i], &tmp, 0);
//		status = WEXITSTATUS(tmp);
//		i++;
//	}
//}

/*get_lines tester*/

//int	main(int argc, char **argv)
//{
//	int		fd;
//	char	*lines;

//	if (argc < 2)
//		return (1);
//	fd = open(argv[1], O_RDONLY);
//	lines = get_lines(fd);
//	ft_putendl_fd(lines, 1);
//	free(lines);
//	(void)argc;
//	return (0);
//}

//char	*get_lines(int fd)
//{
//	char	*line;
//	char	tmp[101];
//	char	*fptr;
//	int		count;

//	line = NULL;
//	while (1)
//	{
//		count = read(fd, tmp, 100);
//		if (count <= 0)
//			return (NULL);
//		tmp[count] = '\0';
//		fptr = line;
//		line = ft_strjoin(line, tmp);
//		free(fptr);
//		if (!line)
//			return (NULL);
//		ft_bzero(tmp, sizeof(char) * 101);
//		if (count < 100)
//			return (line);
//	}
//}
