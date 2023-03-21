/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocabas <mkocabas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 09:46:27 by mkocabas          #+#    #+#             */
/*   Updated: 2023/03/20 18:06:16 by mkocabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
//> ./pipex file1 cmd1 cmd2 file2
// file1 cmd1 | cmd2 > file2
//./pipex infile ``ls -l'' ``wc -l'' outfile


/*
char *get_path(char *cmd) {
    char *path_env = getenv("PATH");
    char *dir, *p, *full_path, *ret;
    int len_cmd = strlen(cmd);

    if (!path_env) {
        printf("PATH env variable not set\n");
        return NULL;
    }

    p = path_env;
    while ((dir = strtok(p, ":")) != NULL) {
        p = NULL;
        int len_dir = strlen(dir);
        full_path = malloc(len_dir + len_cmd + 2);
        if (!full_path) {
            perror("malloc");
            return NULL;
        }
        snprintf(full_path, len_dir + len_cmd + 2, "%s/%s", dir, cmd);
        if (access(full_path, X_OK) == 0) {
            ret = full_path;
            break;
        }
        free(full_path);
    }

    if (!ret) {
        printf("%s: command not found\n", cmd);
        return NULL;
    }

    return ret;
}
*/

int	str_ichr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (i);
	return (-1);
}
char	*path_join(char *path, char *bin)
{
	char	*joined;
	int		i;
	int		j;

	joined = malloc(sizeof(char) * (str_ichr(path, 0) + str_ichr(bin, 0) + 2));
	i = 0;
	j = 0;
	while (path[j])
		joined[i++] = path[j++];
	joined[i++] = '/';
	j = 0;
	while (bin[j])
		joined[i++] = bin[j++];
	joined[i] = 0;
	return (joined);
}

int	str_ncmp(char *str1, char *str2, int n)
{
	while (--n > 0 && *str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*str2 - *str1);
}



char	*str_ndup(char *str, unsigned int n)
{
	char				*duped;
	unsigned int		i;

	i = 0;
	duped = malloc(sizeof(char) * (n + 1));
	while (i < n)
		duped[i++] = *str++;
	duped[n] = 0;
	return (duped);
}

char	**str_split(char *str, char sep)
{
	char	**tab;
	int		count;
	int		i;
	int		j;

	count = 0;
	j = 0;
	while (str[j])
	{
		if (str[j++] == sep)
			count++;
	}
	tab = malloc(sizeof(char *) * (count + 2));
	tab[count + 1] = NULL;
	i = 0;
	while (i < count + 1)
	{
		j = 0;
		while (str[j] && str[j] != sep)
			j++;
		tab[i++] = str_ndup(str, j);
		str = str + j + 1;
	}
	return (tab);
}

char	*get_path(char *cmd, char **env)
{
	char	*path;
	char	*dir;
	char	*bin;
	int		i;

	i = 0;
	while (env[i] && str_ncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (cmd);
	path = env[i] + 5;
	while (path && str_ichr(path, ':') > -1)
	{
		dir = str_ndup(path, str_ichr(path, ':'));
		bin = path_join(dir, cmd);
		free(dir);
		if (access(bin, F_OK) == 0)
			return (bin);
		free(bin);
		path += str_ichr(path, ':') + 1;
	}
	return (cmd);
}

void	exec(char *cmd, char **env)
{
	char	**args;
	char	*path;

	args = str_split(cmd, ' ');
	printf("args[0] :%s \n",args[0]);
	if (str_ichr(args[0], '/') > -1)
	{	
		path = args[0];
	}

	else
	{
		printf("path :%s", path);
		path = get_path(args[0], env);
	}
	execve(path, args, env);
	write(2, "pipex: ", 7);
	write(2, cmd, str_ichr(cmd, 0));
	write(2, ": command not found\n", 20);
	exit(127);
}



int main(int argc, char **argv, char **envp) {
    // if (argc < 2) {
    //     fprintf(stderr, "Usage: %s command\n", argv[0]);
    //     return 1;
    // }
    
    // char *path = get_path(argv[1], envp);
    // if (path) {
    //     printf("PATH: %s\n", path);
    //     free(path);
    // }

	exec("grep -o *",envp);


    return 0;
}
/*
char *get_path(char *cmd, char **envp) {
    char *path_env = NULL;
    char *dir, *p, *full_path, *ret = NULL;
    int len_cmd = strlen(cmd);

    for (int i = 0; envp[i] != NULL; i++) {
        if (strncmp(envp[i], "PATH=", 5) == 0) {
            path_env = envp[i] + 5;
            break;
        }
    }

    if (!path_env) {
        printf("PATH env variable not set\n");
        return NULL;
    }

    p = path_env;
    while ((dir = strtok(p, ":")) != NULL) {
        p = NULL;
        int len_dir = strlen(dir);
        full_path = malloc(len_dir + len_cmd + 2);
        if (!full_path) {
            perror("malloc");
            return NULL;
        }
        snprintf(full_path, len_dir + len_cmd + 2, "%s/%s", dir, cmd);
        if (access(full_path, X_OK) == 0) {
            ret = full_path;
            break;
        }
        free(full_path);
    }

    if (!ret) {
        printf("%s: command not found\n", cmd);
        return NULL;
    }

    return ret;
}
*/