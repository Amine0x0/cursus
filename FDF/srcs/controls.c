/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:57:04 by amabbadi          #+#    #+#             */
/*   Updated: 2025/04/05 16:57:05 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

/*the main controls utility*/
static void	draw_control_line(t_data *data, t_control *ctrl, char *text)
{
	mlx_string_put(data->mlx, data->win, ctrl->left_margin, *ctrl->y_offset,
		0xFFFFFF, text);
	*ctrl->y_offset += 25;
}

static void	draw_projection_info(t_data *data, t_control *ctrl)
{
	char	*projection;

	projection = get_projection_name(data);
	mlx_string_put(data->mlx, data->win, ctrl->left_margin, *ctrl->y_offset,
		0xFFFFFF, "Projection (P): ");
	mlx_string_put(data->mlx, data->win, ctrl->left_margin + 120,
		*ctrl->y_offset, 0x00FF00, projection);
	*ctrl->y_offset += 25;
}

static void	draw_controls_text(t_data *data, int *y_offset, int left_margin)
{
	t_control	ctrl;

	ctrl.y_offset = y_offset;
	ctrl.left_margin = left_margin;
	draw_control_line(data, &ctrl, "CONTROLS:");
	draw_control_line(data, &ctrl, "Arrows: Rotate");
	draw_control_line(data, &ctrl, "WASD: Move");
	draw_control_line(data, &ctrl, "I/O: Zoom");
	draw_control_line(data, &ctrl, "R: Toggle Rotation");
	draw_projection_info(data, &ctrl);
	draw_control_line(data, &ctrl, "ESC: Quit");
}

void	draw_controls(t_data *data)
{
	int	y_offset;
	int	left_margin;

	y_offset = 20;
	left_margin = 30;
	draw_controls_text(data, &y_offset, left_margin);
}
