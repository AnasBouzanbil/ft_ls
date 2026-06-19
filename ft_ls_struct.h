#ifndef ft_LS_struct_h
# define ft_LS_struct_h

#include <stdlib.h>   
#include <unistd.h>   
#include <sys/types.h>
#include <sys/stat.h>  
#include <dirent.h>   
#include <pwd.h>       
#include <grp.h>   
#include <time.h>      
#include <stdbool.h>
#include <string.h>     
#include <errno.h>    

typedef struct s_file
{
    struct stat file_stat;
    char *group_name;
    char *user_name;
    char *permissions;
    char *nlink;
    char *time;
    char *size;
    char *name;
    struct s_file *next;
    struct s_file *prev;
}   t_file;

typedef struct s_dir
{
    struct s_file *files;
    char *namepath;
    struct s_dir *next;
    
}   t_dir;

typedef struct s_ls
{
    t_dir   *dirs;
    char    *options;
    char    **paths;
    int     path_count;
}   t_ls;

#endif