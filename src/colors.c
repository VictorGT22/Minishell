/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:17:12 by vics              #+#    #+#             */
/*   Updated: 2024/02/04 18:39:00 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void blue(void)
{
	printf("\034[0;34m");
}

void red(void)
{
	printf("\030[0m");
}

void purple(void)
{
	printf("\032[0;34m");
}

void yellow(void)
{
	printf("\031[0m");
}

void green(void)
{
	printf("\033[0;32m");
}

void resetColor(void)
{
	printf("\033[0m");
}