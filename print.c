#include "ft_ls.h"

// ================================
// print dyal wahd file f format -l
// ================================
void    print_file_long(t_file *file)
{
    if (file->permissions[0] == 'd')
        ft_putstr("\033[34;1m");
    else
        ft_putstr("\033[0m");
    ft_putstr(file->permissions);
    ft_putstr(" ");
    ft_putstr(file->nlink);
    ft_putstr(" ");
    ft_putstr(file->user_name);
    ft_putstr(" ");
    ft_putstr(file->group_name);
    ft_putstr(" ");
    ft_putstr(file->size);
    ft_putstr(" ");
    ft_putstr(file->time);
    ft_putstr(" ");
    ft_putstr(file->name);
    ft_putstr("\033[0m\n");
}

void    print_lists(t_ls *ls)
{
    t_dir   *current_dir;
    t_file  *current_file;
    t_file  *f;
    long long total;
    char    *total_str;

    current_dir = ls->dirs;
    while (current_dir != NULL)
    {
        current_file = current_dir->files;

        // header "path:" (kaykhrj m3a -R, wla ila kano bzaf dyal paths)
        if (ft_ls_is_option_set(ls, 'R'))
        {
            ft_putstr(current_dir->namepath);
            ft_putstr(":\n");
            if (ft_ls_is_option_set(ls, 'l'))
            {
                // total = somme dyal st_blocks dyal ga3 les files
                total = 0;
                f = current_file;
                while (f != NULL)
                {
                    total += f->file_stat.st_blocks;
                    f = f->next;
                }
                total_str = ft_itoa_ll(total / 2);
                ft_putstr("total ");
                ft_putstr(total_str);
                ft_putstr("\n");
                free(total_str);
            }
        }
        else if (ls->path_count > 1)
        {
            ft_putstr(current_dir->namepath);
            ft_putstr(":\n");
        }

        // -r : nbdaw mn lakher dyal liste
        if (ft_ls_is_option_set(ls, 'r'))
        {
            while (current_file != NULL && current_file->next != NULL)
                current_file = current_file->next;
        }

        while (current_file != NULL)
        {
            if (ft_ls_is_option_set(ls, 'l'))
                print_file_long(current_file);
            else
            {
                ft_putstr(current_file->name);
                ft_putstr("  ");
            }
            if (ft_ls_is_option_set(ls, 'r'))
                current_file = current_file->prev;
            else
                current_file = current_file->next;
        }

        if (!ft_ls_is_option_set(ls, 'l'))
            ft_putstr("\n");

        current_dir = current_dir->next;
        if (current_dir != NULL)
            ft_putstr("\n");
    }
}
