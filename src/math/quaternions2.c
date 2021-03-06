/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quaternions2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 18:26:48 by peer          #+#    #+#                 */
/*   Updated: 2020/04/24 18:26:49 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_quat		quat_new(double x, double y, double z, double angle)
{
	t_quat	new;

	angle = deg2rad(angle);
	new.w = cos(angle);
	new.x = x * sin(angle);
	new.y = y * sin(angle);
	new.z = z * sin(angle);
	return (new);
}

t_quat		quat_lookat(t_vec3 to, t_vec3 from)
{
	double	angle;
	t_vec3	up;
	double	len;

	angle = acos(dotproduct(vec3_normalize(to), vec3_normalize(from)));
	up = vec3_normalize(crossproduct(from, to));
	len = vec3_sqr(up);
	if (len < EPSILON && len > -EPSILON)
		up = vec3_new(0.0, 1.0, 0.0);
	return (quat_new(up.x, up.y, up.z, rad2deg(angle)));
}
