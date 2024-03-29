/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:25:53 by amassias          #+#    #+#             */
/*   Updated: 2024/01/15 16:42:20 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/* ************************************************************************** */
/*                                                                            */
/* Includes                                                                   */
/*                                                                            */
/* ************************************************************************** */

# include "opencl.h"

# include <stdlib.h>

/* ************************************************************************** */
/*                                                                            */
/* Header protoypes                                                           */
/*                                                                            */
/* ************************************************************************** */

int				read_file(
					const char *file_path,
					char **file_buffer_ptr,
					size_t *file_size);

void			print_kernel_param(
					t_kernel_arg *arg);

cl_long			read_integer_signed(
					const char *str,
					const char **end_ptr);

cl_ulong		read_integer_unsigned(
					const char *str,
					const char **end_ptr);

cl_double		read_floating(
					const char *str,
					const char **end_ptr);

t_kernel_arg	*get_arg(
					t_cl *cl,
					t_kernel_mandatory_arg arg_index
					);

#endif