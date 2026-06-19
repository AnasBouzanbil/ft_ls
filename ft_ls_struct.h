#ifndef ft_LS_struct_h
# define ft_LS_struct_h

#include <stdlib.h>     // malloc, free, exit
#include <unistd.h>     // write
#include <sys/types.h>
#include <sys/stat.h>   // stat, lstat, S_ISDIR...
#include <dirent.h>     // opendir, readdir, closedir
#include <pwd.h>        // getpwuid
#include <grp.h>        // getgrgid
#include <time.h>       // time, ctime
#include <stdbool.h>
#include <string.h>     // ghi bach najibo declaration dyal strerror
#include <errno.h>      // errno

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