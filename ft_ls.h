#ifndef ft_ls_h
# define ft_ls_h

# include "./ft_ls_struct.h"

size_t  ft_strlen(const char *str);
char    *ft_strchr(const char *str, int c);
int     ft_strcmp(const char *s1, const char *s2);
char    *ft_strdup(const char *src);
char    *ft_strjoin(const char *s1, const char *s2);
char    *ft_build_path(const char *dir, const char *name);
char    *ft_itoa_ll(long long n);
char    *ft_format_time(time_t mtime);

void    ft_putstr(const char *str);
void    ft_putstr_endl(const char *str);

bool    ft_ls_is_option_set(t_ls *ls, char option);

// === ft_ls core ===
void    parse_ft_ls_options(t_ls *ls, int argc, char **argv);
void    ft_ls(t_ls *ls);
void    work_on_directory(t_ls *ls, char *path);
void    insert_file_into_dir(t_dir *dir, t_file *new_file, char *options);
void    ft_ls_add_file(t_dir *dir, char *name, struct stat file_stat, char *options);
void    print_lists(t_ls *ls);
void    print_file_long(t_file *file);
void    ft_free_ft_ls(t_ls *ls);

#endif