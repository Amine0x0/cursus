/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:58:02 by amabbadi          #+#    #+#             */
/*   Updated: 2025/04/05 16:58:03 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"
/*anything rotation based, main logic here is to update the data
on the header file*/
void	handle_rotation_keys(int keycode, t_data *data)
{
	if (keycode == KEY_LEFT)
		data->angle_x -= ANGLE_SPEED;
	else if (keycode == KEY_RIGHT)
		data->angle_x += ANGLE_SPEED;
	else if (keycode == KEY_UP)
		data->angle_y -= ANGLE_SPEED;
	else if (keycode == KEY_DOWN)
		data->angle_y += ANGLE_SPEED;
}

int	update_rotation(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->rotating)
	{
		data->angle_x += ANGLE_SPEED;
		draw_map(data);
	}
	return (0);
}
