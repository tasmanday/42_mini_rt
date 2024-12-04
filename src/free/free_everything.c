/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_everything.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 23:12:25 by tday              #+#    #+#             */
/*   Updated: 2024/12/04 23:33:15 by tday             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/minirt.h"

void free_everything(t_pixel **pixels, t_ray **corners, int width, int height)
{
	// Free the pixels array
	if (pixels)
	{
		int i = 0;
		while (i < height)
		{
			if (pixels[i])
				free(pixels[i]); // Free each row in the pixels array
			i++;
		}
		free(pixels); // Free the top-level pointer
	}

	// Free the corners array
	if (corners)
	{
		int i = 0;
		while (i <= height)
		{
			if (corners[i])
				free(corners[i]); // Free each row in the corners array
			i++;
		}
		free(corners); // Free the top-level pointer
	}
}
