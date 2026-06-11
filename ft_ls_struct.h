#ifndef ft_LS_struct_h
# define ft_LS_struct_h


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <stdbool.h>

// # here i will  hvae a ft_ls class that will contain a :
// linked list of files and directories
// 
typedef struct s_file
{
    // your fields here
    struct stat file_stat; // we will get the mode, time and group and size and mtime from this struct
    char *group_name; // we will get the group name from this field
    char *user_name; // we will get the user name from this field
    char *permissions; // we will get the permissions from this field
    char *time; // we will get the time from this field
    char *size; // we will get the size from this field
    char *date; // we will get the date from this field
    char *year; // we will get the year from this field
    
    char *name;
    struct s_file *next;
    struct s_file *prev;
}   t_file;

typedef struct s_dir
{
    struct s_file *files;

    char *namepath; // we will store the path of the directory here
    struct s_dir *next;
}   t_dir;
typedef struct s_ls
{
    t_dir   *dirs;
    char    *options;
    char    **paths;    // array of paths given by user
    int     path_count;
}   t_ls;


#endif