#include <unistd.h>
#include <stdlib.h>
#include "ft_ls.h"


size_t	ft_strlen(const char *str)
{ // This function counts the number of characters in a string.
	size_t	a;

	a = 0;
	while (str[a] != '\0')
	{
		a++;
	}
	return (a);
}
char	*ft_strchr(const char *str, int c)
{
	char	x;
	size_t	l;
	size_t	i;

	x = (char)c; // Cast the integer c to a char and assign it to the char x. This is done to be able to compare the characters of the string to the character c.
	i = 0;
	l = ft_strlen(str);
	while (l >= i) // Iterate through the string character by character until the end of the string is reached.
	{
		if (str[i] == x) // If the current character is equal to the character c, return the address of the current character.
		{
			return ((char *)str + i); // Cast the address of the current character to a char pointer and return it.
		}
		i++;
	}
	return (0);
}


void   ft_putstr_endl(const char *str)
{
    write(1, str, ft_strlen(str));
    write(1, "\n", 1);
}

bool   ft_ls_is_option_set(t_ls *ls, char option)
{
    if (ft_strchr(ls->options, option))
        return (true);
    return (false);
}
