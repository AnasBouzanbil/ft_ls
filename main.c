#include "ft_ls.h"


void    work_on_directory(t_ls *ls, char *path)
{
    t_dir           *new_dir;
    t_dir           *current;
    DIR             *dir;
    struct dirent   *entry;
    struct stat     file_stat;
    char            *full_path;
    t_file          *f;

    new_dir = malloc(sizeof(t_dir));
    new_dir->namepath = ft_strdup(path);
    new_dir->files = NULL;
    new_dir->next = NULL;

    if (ls->dirs == NULL)
        ls->dirs = new_dir;
    else
    {
        current = ls->dirs;
        while (current->next != NULL)
            current = current->next;
        current->next = new_dir;
    }

    dir = opendir(path);
    if (!dir)
        return;

    while ((entry = readdir(dir)) != NULL)
    {
        full_path = ft_build_path(path, entry->d_name);
        if (lstat(full_path, &file_stat) == -1)
        {
            free(full_path);
            continue;
        }
        if (entry->d_name[0] == '.' && !ft_ls_is_option_set(ls, 'a'))
        {
            free(full_path);
            continue;
        }
        ft_ls_add_file(new_dir, entry->d_name, file_stat, ls->options);
        free(full_path);
    }
    closedir(dir);

if (ft_ls_is_option_set(ls, 'R'))
{
    if (ft_ls_is_option_set(ls, 'r'))
    {
        f = new_dir->files;
        while (f && f->next)
            f = f->next;
        while (f != NULL)
        {
            if (S_ISDIR(f->file_stat.st_mode) &&
                ft_strcmp(f->name, ".") != 0 && ft_strcmp(f->name, "..") != 0)
            {
                full_path = ft_build_path(path, f->name);
                work_on_directory(ls, full_path);
                free(full_path);
            }
            f = f->prev;
        }
    }
    else
    {
        f = new_dir->files;
        while (f != NULL)
        {
            if (S_ISDIR(f->file_stat.st_mode) &&
                ft_strcmp(f->name, ".") != 0 && ft_strcmp(f->name, "..") != 0)
            {
                full_path = ft_build_path(path, f->name);
                work_on_directory(ls, full_path);
                free(full_path);
            }
            f = f->next;
        }
    }
}
}

void    ft_ls(t_ls *ls)
{
    int i;

    i = 0;
    while (i < ls->path_count)
    {
        work_on_directory(ls, ls->paths[i]);
        i++;
    }
}

void    ft_free_ft_ls(t_ls *ls)
{
    t_dir   *current_dir;
    t_dir   *temp_dir;
    t_file  *current_file;
    t_file  *temp_file;

    current_dir = ls->dirs;
    while (current_dir != NULL)
    {
        current_file = current_dir->files;
        while (current_file != NULL)
        {
            temp_file = current_file;
            current_file = current_file->next;
            free(temp_file->name);
            free(temp_file->group_name);
            free(temp_file->user_name);
            free(temp_file->permissions);
            free(temp_file->nlink);
            free(temp_file->time);
            free(temp_file->size);
            free(temp_file);
        }
        temp_dir = current_dir;
        current_dir = current_dir->next;
        free(temp_dir->namepath);
        free(temp_dir);
    }
    free(ls->options);
    free(ls->paths);
    free(ls);
}

int main(int argc, char **argv)
{
    t_ls *ls;

    ls = malloc(sizeof(t_ls));
    ls->options = malloc(6); 
    ls->options[0] = '\0';
    ls->paths = malloc(sizeof(char *) * argc);
    ls->path_count = 0;
    ls->dirs = NULL;

    parse_ft_ls_options(ls, argc, argv);
    ft_ls(ls);
    print_lists(ls);
    ft_free_ft_ls(ls);

    return (0);
}