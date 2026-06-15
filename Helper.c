#include "ft_ls.h"

// ================================
// libft basique
// ================================

size_t  ft_strlen(const char *str)
{
    size_t a;

    a = 0;
    while (str[a] != '\0')
        a++;
    return (a);
}

char    *ft_strchr(const char *str, int c)
{
    char    x;
    size_t  i;

    x = (char)c;
    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == x)
            return ((char *)str + i);
        i++;
    }
    if (x == '\0')
        return ((char *)str + i);
    return (NULL);
}

// ghir bdlna strcmp lia mn libc
int     ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && *s1 == *s2)
    {
        s1++;
        s2++;
    }
    return ((unsigned char)*s1 - (unsigned char)*s2);
}

// strdup b yedna : kaymalloci w kaynsa3
char    *ft_strdup(const char *src)
{
    char    *dst;
    size_t  i;

    dst = malloc(ft_strlen(src) + 1);
    if (!dst)
        return (NULL);
    i = 0;
    while (src[i] != '\0')
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
    return (dst);
}

// kaylsq jouj strings f wahd jdid (malloc)
char    *ft_strjoin(const char *s1, const char *s2)
{
    char    *res;
    size_t  l1;
    size_t  l2;
    size_t  i;
    size_t  j;

    l1 = ft_strlen(s1);
    l2 = ft_strlen(s2);
    res = malloc(l1 + l2 + 1);
    if (!res)
        return (NULL);
    i = 0;
    while (i < l1)
    {
        res[i] = s1[i];
        i++;
    }
    j = 0;
    while (j < l2)
    {
        res[i + j] = s2[j];
        j++;
    }
    res[i + j] = '\0';
    return (res);
}

// bach nbniw path: "dir" + "/" + "name" -> "dir/name"
// hadi ghadi t3awd snprintf("%s/%s", ...)
char    *ft_build_path(const char *dir, const char *name)
{
    char    *tmp;
    char    *res;

    tmp = ft_strjoin(dir, "/");
    if (!tmp)
        return (NULL);
    res = ft_strjoin(tmp, name);
    free(tmp);
    return (res);
}

// kifkif itoa, t7awl number l string (malloc)
// ghadi nsta3mlouha l size, nlink w total
char    *ft_itoa_ll(long long n)
{
    char                buf[24];
    int                 i;
    int                 neg;
    unsigned long long  un;

    i = 22;
    buf[23] = '\0';
    neg = 0;
    if (n < 0)
    {
        neg = 1;
        un = (unsigned long long)(-n);
    }
    else
        un = (unsigned long long)n;
    if (un == 0)
        buf[i--] = '0';
    while (un > 0)
    {
        buf[i--] = (un % 10) + '0';
        un /= 10;
    }
    if (neg)
        buf[i--] = '-';
    return (ft_strdup(&buf[i + 1]));
}

// ================================
// write wrappers (bdal printf)
// ================================

void    ft_putstr(const char *str)
{
    write(1, str, ft_strlen(str));
}

void    ft_putstr_endl(const char *str)
{
    write(1, str, ft_strlen(str));
    write(1, "\n", 1);
}

// ================================
// formatage dyal date
// strftime/localtime machi f la liste l mosma7a,
// so we use ctime() (mosma7a) w nqas9o منها li bghina
// ctime() kaytl3 lina: "Www Mmm dd hh:mm:ss yyyy\n"
//           index:       0   4  8  11      20    24
// ================================
char    *ft_format_time(time_t mtime)
{
    char        *c;
    char        *res;
    time_t      now;
    int         i;
    int         j;
    const long  six_months = 15552000; // ~ 180 jour b secondes

    c = ctime(&mtime);
    now = time(NULL);
    res = malloc(13);
    if (!res)
        return (NULL);
    i = 0;
    j = 4;
    while (j < 10) // "Mmm dd" (6 caracteres)
        res[i++] = c[j++];
    if ((now - mtime) > six_months || (mtime - now) > six_months)
    {
        // file قديم/futur bzaf -> nwriw l'année bdal l'heure
        res[i++] = ' ';
        res[i++] = ' ';
        j = 20;
        while (j < 24) // "yyyy"
            res[i++] = c[j++];
    }
    else
    {
        res[i++] = ' ';
        j = 11;
        while (j < 16) // "hh:mm"
            res[i++] = c[j++];
    }
    res[i] = '\0';
    return (res);
}

bool    ft_ls_is_option_set(t_ls *ls, char option)
{
    if (ft_strchr(ls->options, option))
        return (true);
    return (false);
}