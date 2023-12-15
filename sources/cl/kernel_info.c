/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 21:19:49 by amassias          #+#    #+#             */
/*   Updated: 2023/12/15 13:02:30 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/* Inlcudes                                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "opencl.h"

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

int	cl_get_kernel_info__int(
		cl_kernel kernel,
		cl_kernel_info info,
		void *value)
{
	cl_int	error_code;

	error_code = clGetKernelInfo(
			kernel, info,
			sizeof(cl_int), value,
			NULL);
	if (error_code != CL_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	cl_get_kernel_info__str(
		cl_kernel kernel,
		cl_kernel_info info,
		void **string_ptr)
{
	cl_int	error_code;
	size_t	size;

	error_code = clGetKernelInfo(
			kernel, info,
			0, NULL,
			&size);
	if (error_code != CL_SUCCESS)
		return (EXIT_FAILURE);
	*string_ptr = (void *) malloc(size);
	error_code = clGetKernelInfo(
			kernel, info,
			size, *string_ptr,
			NULL);
	if (error_code != CL_SUCCESS)
		return (free(*string_ptr), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
