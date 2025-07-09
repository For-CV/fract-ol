#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/*
DESCRIPTION
       The atoi() function converts the initial portion of the string pointed to by nptr to int.  The behavior is the same as

           strtol(nptr, NULL, 10);

       except that atoi() does not detect errors.

       The  atol()  and atoll() functions behave the same as atoi(), except that they convert the initial portion of the string to their
       return type of long or long long.

RETURN VALUE
       The converted value or 0 on error.
*/

long     ft_atol(const char *str)
{
        int     sign;
        long     result;
        int     i;

        result = 0;
        i = 0;
        sign = 1;
        if (!str)
                return (0);
        while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
                i++;
        if (str[i] == '-' || str[i] == '+')
        {
                sign = 1 - 2 * (str[i] == '-');
                i++;
        }
        while (str[i] >= '0' && str[i] <= '9')
        {
                result = result * 10 + (str[i] - '0');
                i++;
        }
        return (sign * result);
}