#include "ft_ls.h"





// ================================
// insertion triée (default = nom, -t = mtime)
// ================================
void    insert_file_into_dir(t_dir *dir, t_file *new_file, char *options)
{
    t_file  *current;
    t_file  *last;

    if (dir->files == NULL)
    {
        dir->files = new_file;
        return;
    }
    current = dir->files;
    if (ft_strchr(options, 't'))
    {
        while (current != NULL)
        {
            if (new_file->file_stat.st_mtime > current->file_stat.st_mtime)
                break;
            if (new_file->file_stat.st_mtime == current->file_stat.st_mtime
                && ft_strcmp(new_file->name, current->name) < 0)
                break;
            current = current->next;
        }
    }
    else
    {
        while (current != NULL)
        {
            if (ft_strcmp(new_file->name, current->name) < 0)
                break;
            current = current->next;
        }
    }
    if (current == dir->files) // here we insert at the beginning b
    {
        new_file->next = dir->files;
        dir->files->prev = new_file;
        dir->files = new_file;
    }
    else if (current == NULL) // here we insert at the end because we reached the end of the list
    {
        last = dir->files;
        while (last->next != NULL)
            last = last->next;
        last->next = new_file;
        new_file->prev = last;
    }
    else
    {
        new_file->next = current;
        new_file->prev = current->prev;
        current->prev->next = new_file;
        current->prev = new_file;
    }
}

void    ft_ls_add_file(t_dir *dir, char *name, struct stat file_stat, char *options)
{
    t_file          *new_file;
    struct group    *grp;
    struct passwd   *pwd;
    char            permissions[11];

    new_file = malloc(sizeof(t_file));
    new_file->name = ft_strdup(name);
    new_file->group_name = NULL;
    new_file->user_name = NULL;
    new_file->permissions = NULL;
    new_file->nlink = NULL;
    new_file->time = NULL;
    new_file->size = NULL;

    if (ft_strchr(options, 'l'))
    {
        pwd = getpwuid(file_stat.st_uid);
        if (pwd)
            new_file->user_name = ft_strdup(pwd->pw_name);
        else
            new_file->user_name = ft_itoa_ll((long long)file_stat.st_uid);
        
        grp = getgrgid(file_stat.st_gid);
        if (grp)
            new_file->group_name = ft_strdup(grp->gr_name);
        else
            new_file->group_name = ft_itoa_ll((long long)file_stat.st_gid);

        permissions[0] = S_ISDIR(file_stat.st_mode) ? 'd' : '-';
        permissions[1] = (file_stat.st_mode & S_IRUSR) ? 'r' : '-';
        permissions[2] = (file_stat.st_mode & S_IWUSR) ? 'w' : '-';
        permissions[3] = (file_stat.st_mode & S_IXUSR) ? 'x' : '-';
        permissions[4] = (file_stat.st_mode & S_IRGRP) ? 'r' : '-';
        permissions[5] = (file_stat.st_mode & S_IWGRP) ? 'w' : '-';
        permissions[6] = (file_stat.st_mode & S_IXGRP) ? 'x' : '-';
        permissions[7] = (file_stat.st_mode & S_IROTH) ? 'r' : '-';
        permissions[8] = (file_stat.st_mode & S_IWOTH) ? 'w' : '-';
        permissions[9] = (file_stat.st_mode & S_IXOTH) ? 'x' : '-';
        permissions[10] = '\0';
        new_file->permissions = ft_strdup(permissions);

        new_file->time = ft_format_time(file_stat.st_mtime);
        new_file->size = ft_itoa_ll((long long)file_stat.st_size);
        new_file->nlink = ft_itoa_ll((long long)file_stat.st_nlink);
    }

    new_file->file_stat = file_stat;
    new_file->next = NULL;
    new_file->prev = NULL;
    insert_file_into_dir(dir, new_file, options);
}
