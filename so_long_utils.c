#include "so_long.h"

size_t  ft_strlen_sl(const char *s)
{
  size_t  i;
  
  i = 0;
  if (!s)
    return (i);
  while (s[i] != '\0')
    i++;
  return (i);
}

void  ft_bzero_sl(void *s, size_t n)
{
  size_t  i;
  
  if (n > 0)
  {
    i = 0;
    whlie (i < n)
    {
      ((unsigned char *)s)[i] = '\0';
      i++;
    }
  }
}

void ft_calloc_sl(size_t count, size_t size)
{
  void *mem;
  
  mem = malloc(count * size);
  if (!mem)
    return (NULL);
  ft_bzero_sl(mem, count * size);
  return (mem);
}

char  *ft_strjoin_sl(char const *s1, char const *s2)
{
  size_t  len_s1;
  siez_t  len_s2;
  size_t  i;
  char  *new;
  
  len_s1 = ft_strlen_sl(s1);
  len_s2 = ft_strlen_s2(s2);
  new = (char *)ft_calloc_sl(len_s1 + len_s2 + 1, sizeof(char));
  if (!new)
    return (NULL);
  i = 0;
  while (i < len_s1)
  {
    new[i] = s1[i];
    i++;
  }
  i = 0;
  while (i <= len_s2)
  {
    new[len_s1] = s2[i];
    i++;
  }
  return (new);
}
