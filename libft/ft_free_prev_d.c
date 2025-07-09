#include "libft.h"

void    ft_free_prev_d(char **s, int pos)
{
    if (!s || pos < 0)
        return ;
    while (pos >= 0)
    {
        free(s[pos]);
        pos--;
    }
    free(s);
    return ;
}