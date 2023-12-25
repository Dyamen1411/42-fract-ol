/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 05:14:29 by amassias          #+#    #+#             */
/*   Updated: 2023/12/25 07:14:27 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file opencl_init.c
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2023-12-25
 * @copyright Copyright (c) 2023
 */

/* ************************************************************************** */
/*                                                                            */
/* Includes                                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "opencl.h"
#include "utils.h"

#include <libft.h>

/* ************************************************************************** */
/*                                                                            */
/* Defines                                                                    */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief The path of the OpenCL program to load.
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2023-12-25
 */
#define PROGRAM_PATH "kernels/fract-ol_kernels.cl"

/**
 * @brief Build options for the OpenCL program.
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2023-12-25
 */
#define PROGRAM_BUILD_OPTIONS \
"-cl-kernel-arg-info -cl-fast-relaxed-math -cl-mad-enable"

/* ************************************************************************** */
/*                                                                            */
/* Helper protoypes                                                           */
/*                                                                            */
/* ************************************************************************** */

/**
 * If a build error occurs, a message and a log will be printed on standard
 * error.
 * @brief Build an OpenCL program.
 * @param cl A pointer to a valid OpenCL context.
 * @retval CL_CODE_SUCCESS if no error occured
 * @retval CL_CODE_PROGRAM_BUILD_FAILURE if an error occured.
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2023-12-25
 */
static t_cl_code	_build_program(
						t_cl *cl
						);

/**
 * @brief Initializes the program.
 * @param cl A pointer to a valid OpenCL context.
 * @retval CL_CODE_SUCCESS if no error occured
 * @retval CL_CODE_PROGRAM_INITIALIZATION_FAILURE if any error occured.
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2023-12-25
 */
static t_cl_code	_initialize_program(
						t_cl *cl
						);

/**
 * 
 * @brief Initializes 
 * @param cl 
 * @returns t_cl_code 
 * @author Antoine Massias (amassias@student.42lehavre.fr)
 * @date 2023-12-25
 */
static t_cl_code	_initialize_kernels(
						t_cl *cl
						);

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

t_cl_code	opencl_init(
				t_cl *cl
				)
{
	size_t	c;
	cl_int	code;

	ft_bzero(cl, sizeof(*cl));
	code = clGetPlatformIDs(1, &cl->platform, &c);
	if (c == 0 || code != CL_SUCCESS)
		return (CL_CODE_NO_PLATFORM);
	code = clGetDeviceIDs(cl->platform, CL_DEVICE_TYPE_ALL, 1, &cl->device, &c);
	if (c == 0 || code != CL_SUCCESS)
		return (opencl_cleanup(cl), CL_CODE_NO_DEVICE);
	cl->context = clCreateContext(NULL, 1, &cl->device, NULL, NULL, &code);
	if (code != CL_SUCCESS)
		return (opencl_cleanup(cl), CL_CODE_CONTEXT_INITIALIZATION_FAILURE);
	cl->command_queue = clCreateCommandQueueWithProperties(
			cl->context, cl->device, NULL, &code);
	if (code != CL_SUCCESS)
		return (opencl_cleanup(cl),
			CL_CODE_COMMAND_QUEUE_INITIALIZATION_FAILURE);
	code = _initialize_kernels(cl);
	if (code != CL_CODE_SUCCESS)
		return (opencl_cleanup(cl), code);
	return (CL_CODE_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/* Helper implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

static t_cl_code	_initialize_program(
						t_cl *cl
						)
{
	cl_int	code;
	char	*source;
	size_t	size;

	code = read_file_in_buffer(PROGRAM_PATH, &source, &size);
	if (code != 0)
		return (CL_CODE_PROGRAM_INITIALIZATION_FAILURE);
	cl->program = clCreateProgramWithSource(
			cl->context, 1, &source, &size, &code);
	free(source);
	if (code)
		return (CL_CODE_PROGRAM_INITIALIZATION_FAILURE);
	return (CL_CODE_SUCCESS);
}

static t_cl_code	_build_program(
						t_cl *cl
						)
{
	cl_int	code;
	char	*log;
	size_t	log_size;

	code = clBuildProgram(
			cl->program, 1, &cl->device, PROGRAM_BUILD_OPTIONS, NULL, NULL);
	if (code == CL_SUCCESS)
		return (CL_CODE_SUCCESS);
	ft_fprintf(STDERR_FILENO, "Build error (%s):\n", code);
	code = clGetProgramBuildInfo(
			cl->program, cl->device, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
	if (code != CL_SUCCESS)
		return (CL_CODE_PROGRAM_BUILD_FAILURE);
	log = (char *) malloc(log_size);
	if (log == NULL)
		return (CL_CODE_PROGRAM_BUILD_FAILURE);
	code = clGetProgramBuildInfo(
			cl->program, cl->device, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
	if (code == CL_SUCCESS)
		ft_printf("%s\n", log);
	free(log);
	return (CL_CODE_PROGRAM_BUILD_FAILURE);
}

static t_cl_code	_initialize_kernels(
						t_cl *cl
						)
{
	cl_int	code;

	code = _initialize_program(cl);
	if (code)
		return (code);
	code = _build_program(cl);
	if (code)
		return (code);
	return (CL_CODE_SUCCESS);
}
