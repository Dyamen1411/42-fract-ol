/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_kernels.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 21:13:09 by amassias          #+#    #+#             */
/*   Updated: 2023/12/20 20:26:00 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/* Includes                                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "opencl.h"

#include <libft.h>

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

void	cleanup_kernels(
			t_cl *cl,
			size_t count)
{
	t_kernel	*kernel;

	if (cl->kernels == NULL)
		return ;
	while (count-- > 0)
	{
		kernel = &cl->kernels[count];
		if (kernel == NULL)
			continue ;
		while (kernel->arg_count-- > 0)
			free((void *)kernel->args[kernel->arg_count].name);
		free((void *)kernel->args);
		free((void *)kernel->_arg_values);
		clReleaseKernel(kernel->kernel);
	}
	free((void *)cl->_kernel_names);
	free((void *)cl->kernels);
	cl->kernels = NULL;
}
