/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 02:54:55 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/25 10:30:39 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CTX_H
# define CTX_H

# include "libs.h"

# define VALID_FLAGS "lRart"
/*
	Mandatory flags: lRart
	
	-l:
		use a long listing format
	-R:
		list subdirectories recursively
	-a:
		do not ignore entries starting with .
	-r:
		reverse order while sorting
	-t:
		sort by time, newest first
*/
typedef struct s_flags
{
	bool	l_flag;
	bool	R_flag;
	bool	a_flag;
	bool	t_flag;
	bool	r_flag;
}	t_flags;

typedef struct s_file
{
	char	*name;
	char	*path;

	bool			is_dir;
	struct s_file	*dir;

	struct s_file	*next;
}	t_file;

// typedef struct	s_directory
// {
// 	t_file	*files;
// }	t_directory;

t_file	*files_last(t_file *lst);
void	files_add_back(t_file **lst, t_file *new);
int		files_size(t_file *lst);
t_file	*files_new(char *name, char *parent_path);

typedef struct s_ctx
{
	t_flags	flags;
	t_list	*args;
	t_file	*files;
}	t_ctx;

int		ctx_init(t_ctx *ctx, char **av);

int		ctx_parse_args(t_ctx *ctx, char **av);
void	empty_del(void *ptr);

int		ctx_delete(t_ctx *ctx);

void	*error(char *str);

#endif
