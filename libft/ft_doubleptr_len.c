int ft_doubleptr_len(char **dptr)
{
    int i;

    i = 0;
    while (dptr[i])
        i++;
    return (i);
}