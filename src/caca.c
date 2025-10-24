// void	print_dirent(t_ctx *ctx, struct dirent *dirent, char *path)
// {
// 	if (!dirent)
// 		return ;

// 	if (dirent->d_name[0] == '.' && !ctx->flags.a_flag)
// 		return ;

// 	struct stat	file_stat;

// 	if (stat(path, &file_stat) == -1)
// 		return perror("1");

// 	char	*time_string = ctime(&file_stat.st_ctime);
// 	time_string[16] = 0;

// 	struct passwd *passwd = getpwuid(file_stat.st_uid);
// 	if (!passwd)
// 		return perror("2");
// 	struct group *group = getgrgid(file_stat.st_gid);
// 	if (!group)
// 		return perror("3");

// 	if (ctx->flags.l_flag)
// 		printf("%lu %s %s %ld	%s %s\n", file_stat.st_nlink, passwd->pw_name, group->gr_name, file_stat.st_size, time_string, dirent->d_name);
// 	else
// 		printf("%s\n", dirent->d_name);
// }
