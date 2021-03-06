/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_cylinder.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer <pde-bakk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 18:28:50 by peer          #+#    #+#                 */
/*   Updated: 2020/05/07 05:50:37 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cylhelp	cylinder_calc(t_cylinder *cyl, t_data *my_mlx, int threadnr)
{
	t_cylhelp	help;

	help.rayorigin = my_mlx->cam->s;
	help.raydir = my_mlx->ray[threadnr]->v;
	help.cylcenter = cyl->s;
	help.cylrot = cyl->v;
	help.dist = vec3_sub(help.rayorigin, help.cylcenter);
	help.c1 = vec3_sub(help.raydir,
			vec3_mult(help.cylrot, dotproduct(help.raydir, help.cylrot)));
	help.c2 = vec3_sub(help.dist,
			vec3_mult(help.cylrot, dotproduct(help.dist, help.cylrot)));
	help.abc0 = vec3_sqr(help.c1);
	help.abc1 = 2.0 * dotproduct(help.c1, help.c2);
	help.abc2 = vec3_sqr(help.c2) - pow(cyl->diameter / 2, 2);
	help.p1 = vec3_sub(help.cylcenter,
			vec3_mult(help.cylrot, cyl->height / 2.0));
	help.p2 = vec3_add(help.cylcenter,
			vec3_mult(help.cylrot, cyl->height / 2.0));
	return (help);
}

int			solve_quadratic_equation(t_cylhelp *help)
{
	double	discriminant;

	discriminant = pow(help->abc1, 2) - 4.0 * help->abc0 * help->abc2;
	if (discriminant < 0.0)
		return (0);
	else if (discriminant < EPSILON)
	{
		help->t0 = -0.5 * help->abc1 / help->abc0;
		help->t1 = help->t0;
	}
	else
	{
		help->t0 = (-help->abc1 + sqrt(discriminant)) / (2.0 * help->abc0);
		help->t1 = (-help->abc1 - sqrt(discriminant)) / (2.0 * help->abc0);
	}
	return (1);
}

void		cylinder_hit(t_data *my_mlx, int threadnr, t_cylinder *cyl,
		t_cylhelp help)
{
	if (help.res > EPSILON && help.res < my_mlx->ray[threadnr]->length)
	{
		my_mlx->ray[threadnr]->length = help.res;
		help.res = -1.0;
		my_mlx->ray[threadnr]->colour = cyl->colour;
		my_mlx->ray[threadnr]->hitnormal = vec3_normalize(vec3_sub(vec3_add(
	my_mlx->cam->s, vec3_mult(my_mlx->ray[threadnr]->v, help.res)), cyl->s));
	}
}

void		get_dotproducts(double dotp[4], t_cylhelp help)
{
	t_vec3	q;

	q = vec3_add(help.rayorigin, vec3_mult(help.raydir, help.t0));
	dotp[0] = dotproduct(help.cylrot, vec3_sub(q, help.p1));
	dotp[1] = dotproduct(help.cylrot, vec3_sub(q, help.p2));
	q = vec3_add(help.rayorigin, vec3_mult(help.raydir, help.t1));
	dotp[2] = dotproduct(help.cylrot, vec3_sub(q, help.p1));
	dotp[3] = dotproduct(help.cylrot, vec3_sub(q, help.p2));
}

int			find_cylinder(t_cylinder *cyl, t_data *my_mlx, int threadnr)
{
	t_cylhelp	help;
	double		dotp[4];

	ft_bzero(&help, sizeof(t_cylhelp));
	help = cylinder_calc(cyl, my_mlx, threadnr);
	help.res = -1.0;
	if (solve_quadratic_equation(&help) == 1)
	{
		get_dotproducts(dotp, help);
		if (help.t0 > EPSI && dotp[0] > 0.0 && dotp[1] < 0.0)
		{
			help.res = help.t0;
		}
		if (help.t1 > EPSI && dotp[2] > 0.0 && dotp[3] < 0.0)
		{
			if (help.res != -1)
				help.res = fmin(help.t0, help.t1);
			else
				help.res = help.t1;
		}
		cylinder_hit(my_mlx, threadnr, cyl, help);
		return (1);
	}
	return (0);
}
