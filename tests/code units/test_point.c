#include "../../src/t_point/point.h"
#include <stdio.h>

int	main()
{
	t_point	point;

	point = point2(1,2);

	printf("x = %i, y = %i\n", point.x, point.y);
}
