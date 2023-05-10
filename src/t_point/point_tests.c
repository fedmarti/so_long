#include "point.h"
#include <stdio.h>
#include <unistd.h>

int	main()
{
	unsigned int a;
	unsigned int b;
	int			 res;
	t_point		 vectora;
	t_point		 vectorb;
	
	while (1)
	{
		scanf("%u", &a);
		scanf("%u", &b);
		vectora = point2(a, b);
		printf("vector_a = {%u, %u}\n len = %f\n", vectora.x, vectora.y, point_len(vectora));
		scanf("%u", &a);
		scanf("%u", &b);
		vectorb = point2(a, b);
		printf("vector_b = {%u, %u}\n len = %f\n", vectorb.x, vectorb.y, point_len(vectorb));
		res = point_cmpr(vectora, vectorb);
		if (!res)
			printf ("The two vectors are of the same length\n");
		else if (res > 0)
			printf ("a is longer\n");
		else
			printf ("b is longer\n");
	}
}