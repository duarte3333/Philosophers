#include "../philosophers.h"

//Ocupa n bytes com NULL a partir do elemento para o qual s está a apontar
void	ft_bzero(void *s, size_t n)
{
	char	*str;
	int		i;

	i = -1;
	str = (char *)s;
	while (n > 0)
	{
		str[++i] = 0;
		n--;
	}
}

//O nmemb sao o numero de elementos
//O size representa o numero de bytes 
//que cada elemento ocupa
//Aloca espaco para o array com o malloc
//e preenche com zeros
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;
	size_t	final_size;

	if (nmemb == 0 || size == 0)
	{
		nmemb++;
		size++;
	}
	final_size = nmemb * size;
	p = malloc(final_size);
	if (!p)
		return (NULL);
	ft_bzero(p, final_size);
	return (p);
}