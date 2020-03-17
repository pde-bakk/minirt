/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_uvimg.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/02 15:09:51 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/03/17 01:56:19 by peerdb        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_uvimg(t_data *my_mlx)
{
	if (BONUS == 1)
	{
		if (UV == 1)
			my_mlx->bonus->uvimg = mlx_png_file_to_image(my_mlx->mlx_ptr,
			"textures/pic.png", &my_mlx->bonus->uvnx, &my_mlx->bonus->uvny);
		else
			my_mlx->bonus->uvimg = mlx_png_file_to_image(my_mlx->mlx_ptr,
			"textures/world.png", &my_mlx->bonus->uvnx, &my_mlx->bonus->uvny);
		if (my_mlx->bonus->uvimg != NULL)
			my_mlx->bonus->uvaddr = mlx_get_data_addr(my_mlx->bonus->uvimg, &my_mlx->bonus->uvbpp,
				&my_mlx->bonus->uvll, &my_mlx->bonus->uvendian);
		if (BUMP == 1)
		{
			my_mlx->bonus->bumpimg = mlx_png_file_to_image(my_mlx->mlx_ptr,
			"textures/bump.png", &my_mlx->bonus->bumpnx, &my_mlx->bonus->bumpny);
			printf("bumpnx=%i, bumpny=%i, bumpimg=%p\n", my_mlx->bonus->bumpnx, my_mlx->bonus->bumpny, my_mlx->bonus->bumpimg);
			if (my_mlx->bonus->bumpimg != NULL)
			my_mlx->bonus->bumpaddr = mlx_get_data_addr(my_mlx->bonus->bumpimg,
			&my_mlx->bonus->bumpbpp, &my_mlx->bonus->bumpll, &my_mlx->bonus->bumpendian);
			printf("bpp=%i, ll=%i, endian=%i, addr=%p\n", my_mlx->bonus->bumpbpp, my_mlx->bonus->bumpll, my_mlx->bonus->bumpendian, my_mlx->bonus->bumpaddr);
		}
	}
}
