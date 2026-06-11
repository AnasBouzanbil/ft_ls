#ifndef ft_ls_h
# define ft_ls_h

# include "./ft_ls_struct.h"


void    ft_ls(t_ls *ls);
void    ft_ls_print(t_ls *ls);
void    parse_ft_ls_options(t_ls *ls, int argc, char **argv);

size_t  ft_strlen(const char *str);
char    *ft_strchr(const char *str, int c);

void   ft_ls_add_file(t_dir *dir, char *name, struct stat file_stat, char *options);
void  ft_ls_add_dir(t_ls *ls, char *namepath);
void   ft_ls_sort_files(t_ls *ls); // we will sort the files based on the time 
bool   ft_ls_is_option_set(t_ls *ls, char option); 

#endif