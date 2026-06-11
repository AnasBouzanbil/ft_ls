#include "ft_ls.h"

void parse_ft_ls_options(t_ls *ls, int argc, char **argv)
{
    int i = 1;

    // first loop: collect options
    while (i < argc && argv[i][0] == '-')
    {
        int j = 1;
        while (argv[i][j])
        {
            if (argv[i][j] == 'l' || argv[i][j] == 'a' ||
                argv[i][j] == 't' || argv[i][j] == 'r' || argv[i][j] == 'R')
            {
                //check option wach aslan kain ola la 
                if (!ft_strchr(ls->options, argv[i][j]))
                {
                    int len = ft_strlen(ls->options);
                    ls->options[len] = argv[i][j];
                    ls->options[len + 1] = '\0';
                }
            }
            else
            {
                write(2, "ft_ls: illegal option\n", 22);
                exit(EXIT_FAILURE);
            }
            j++;
        }
        i++;
    }

    // ila kano l paths mawjoudin f arguments, n7otohom f ls->paths
    while (i < argc)
    {
        char *path = argv[i];

        if (access(path, F_OK) == -1)
        {
            write(2, "ft_ls: cannot access '", 22);
            write(2, path, ft_strlen(path));
            write(2, "': No such file or directory\n", 29);
            exit(EXIT_FAILURE);
        }

        ls->paths[ls->path_count] = argv[i];
        ls->path_count++;
        i++;
    }

    // makain ta chi option gha ls bohdha
    if (ls->path_count == 0)
    {
        ls->paths[0] = ".";
        ls->path_count = 1;
    }
}


void print_lists(t_ls *ls)
{
   // okay the print will be like this 
   // we will loop through the directories and print the files in each directory based on the options given by the user
    t_dir *current_dir = ls->dirs;
    while (current_dir != NULL)
    {
       t_file *current_file = current_dir->files;
       
       if (ft_ls_is_option_set(ls, 'R') )
       {
        printf("%s:\n", current_dir->namepath);
        // printf("\n");
        if (ft_ls_is_option_set(ls, 'l') )
{        if (current_file != NULL )
            printf("total %lld\n", (long long)current_file->file_stat.st_blocks / 2);
        else
            printf("total 0\n");
}
        }
        else if (ls->path_count > 1)
        {
            printf("%s:\n", current_dir->namepath);
        }

       if (ft_ls_is_option_set(ls, 'r'))
       {
         // we will take the last node  as head
         while (current_file->next != NULL)
            current_file = current_file->next;          
       }
         while (current_file != NULL)
         {
             if (ft_ls_is_option_set(ls, 'l'))
             {
                 // print in long format
                 // if folder print  with blue color and bold 
                 if (current_file->permissions[0] == 'd')
                    printf("\033[34;1m");
                 else
                    printf("\033[0m");
                 printf("%s %s %s %s %s %s\033[0m\n", current_file->permissions, current_file->user_name, current_file->group_name, current_file->size, current_file->time, current_file->name);

                }
             else
             {
                 // print in short format
                 printf("%s  ", current_file->name);
             }
             if (ft_ls_is_option_set(ls, 'r'))
                current_file = current_file->prev;
             else
                current_file = current_file->next;
         }
         if (!ft_ls_is_option_set(ls, 'l'))
            printf("\n");
         current_dir = current_dir->next;
         if (current_dir != NULL)
            printf("\n");
        
    }
}



// this function will read the directory depending on the path given by the user and will add the files to the list of files in the directory struct

// the recusive function 

void insert_file_into_dir(t_dir *dir, t_file *new_file, char *options)
{
    if (dir->files == NULL)
    {
        dir->files = new_file;
        return;
    }

    if (ft_strchr(options, 't'))
    {
        t_file *current = dir->files;
        while (current != NULL)
        {
            if (new_file->file_stat.st_mtime > current->file_stat.st_mtime)
                break;
            else if (new_file->file_stat.st_mtime == current->file_stat.st_mtime)
            {
                if (strcmp(new_file->name, current->name) < 0)
                    break;
            }
            current = current->next;
        }

        if (current == dir->files)
        {
            new_file->next = dir->files;
            dir->files->prev = new_file;
            dir->files = new_file;
        }
        else if (current == NULL)
        {
            t_file *last = dir->files;
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
    else
    {
        t_file *current = dir->files;
        while (current->next != NULL)
            current = current->next;
        current->next = new_file;
        new_file->prev = current;
    }
}

void ft_ls_add_file(t_dir *dir, char *name, struct stat file_stat, char *options)
{
    t_file *new_file = malloc(sizeof(t_file));
    new_file->name = strdup(name);
    new_file->group_name = NULL;
    new_file->user_name = NULL;
    new_file->permissions = NULL;
    new_file->time = NULL;
    new_file->size = NULL;

    if (ft_strchr(options, 'l')) // if the long format option is set, we will fill the other fields of the file struct
    {
        // we will fill the other fields of the file struct here based on the file_stat and options
        // for example, we can get the group name and user name from the file_stat and store them in the file struct
        struct group *grp = getgrgid(file_stat.st_gid);
        struct passwd *pwd = getpwuid(file_stat.st_uid);
        new_file->group_name = strdup(grp->gr_name);
        new_file->user_name = strdup(pwd->pw_name);

        // we can also get the permissions from the file_stat and store them in the file struct
        char permissions[11];
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
        new_file->permissions = strdup(permissions);

        // we can also get the time from the file_stat and store it in the file struct
        char time_str[20];
        strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&file_stat.st_mtime));
        new_file->time = strdup(time_str);

        // we can also get the size from the file_stat and store it in the file struct
        char size_str[20];
        snprintf(size_str, sizeof(size_str), "%lld", (long long)file_stat.st_size);
        new_file->size = strdup(size_str);
    }
    new_file->file_stat = file_stat;
    new_file->next = NULL;
    new_file->prev = NULL;

    insert_file_into_dir(dir, new_file, options);
}

void work_on_directory(t_ls *ls, char *path)
{
    // create dir node first
    t_dir *new_dir = malloc(sizeof(t_dir));
    new_dir->namepath = strdup(path);
    new_dir->files = NULL;
    new_dir->next = NULL;

    // append dir to ls->dirs list
    if (ls->dirs == NULL)
        ls->dirs = new_dir;
    else
    {
        t_dir *current = ls->dirs;
        while (current->next != NULL)
            current = current->next;
        current->next = new_dir;
    }

    // now read files into this dir
    DIR *dir = opendir(path);
    struct dirent *entry;
    struct stat file_stat;

    while ((entry = readdir(dir)) != NULL)
    {
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        if (stat(full_path, &file_stat) == -1)
            continue;
        if (entry->d_name[0] == '.' && !ft_ls_is_option_set(ls, 'a'))
            continue;
        ft_ls_add_file(new_dir, entry->d_name, file_stat, ls->options);
        if (S_ISDIR(file_stat.st_mode) && ft_ls_is_option_set(ls, 'R') &&
            strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            work_on_directory(ls, full_path);
    }
    closedir(dir);
}
void ft_ls(t_ls *ls)
{
    for (int i = 0; i < ls->path_count; i++)
    {
        work_on_directory(ls, ls->paths[i]);
    }
}

void ft_free_ft_ls(t_ls *ls)
{
    // free all allocated memory for ls struct
    t_dir *current_dir = ls->dirs;
    while (current_dir != NULL)
    {
        t_file *current_file = current_dir->files;
        while (current_file != NULL)
        {
            t_file *temp_file = current_file;
            current_file = current_file->next;
            if (temp_file->name)
                free(temp_file->name);
            if (temp_file->group_name)
                free(temp_file->group_name);
            if (temp_file->user_name)   
                free(temp_file->user_name);
            if (temp_file->permissions)
                free(temp_file->permissions);
            if (temp_file->time)
                free(temp_file->time);
            if (temp_file->size)
                free(temp_file->size);
            free(temp_file);
        }
        t_dir *temp_dir = current_dir;
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
    t_ls *ls = malloc(sizeof(t_ls));

    ls->options = malloc(6);
    ls->options[0] = '\0';
    ls->paths = malloc(sizeof(char *) * argc);
    ls->path_count = 0;
    ls->dirs = NULL;

    parse_ft_ls_options(ls, argc, argv);
    ft_ls(ls);
    print_lists(ls);
    ft_free_ft_ls(ls);

    return 0;
}