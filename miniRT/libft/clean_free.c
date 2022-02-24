#include "libft.h"

void	clean_free(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}
