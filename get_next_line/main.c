#include<stdio.h>
#include<fcntl.h>
#include "get_next_line.h"
#include <libc.h>

__attribute__((destructor))
static void destructor() {
    system("leaks -q a.out");
}

int main(void)
{
	int		fd;
	char	*le = "s.txt";
//	char	*k = "k.txt";
	int		i;
	char	*c;
	//char	*a;

	fd = open(le, O_RDONLY);
	//int se = open(k, O_RDONLY);
	i = 10;
	while (i > 0)
	{
		c = get_next_line(fd);
		//a = get_next_line(se);
		printf("%s", c);
		//printf("%s", a);
		free(c);
		//free(a);
		i--;
	}
	close(fd);
	//close(se);
	return (0);
}
