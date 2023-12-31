/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set__kernel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 00:04:18 by amassias          #+#    #+#             */
/*   Updated: 2023/12/21 03:50:05 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/* Includes                                                                   */
/*                                                                            */
/* ************************************************************************** */

#include "_command_line_internal.h"

/* ************************************************************************** */
/*                                                                            */
/* Defines                                                                    */
/*                                                                            */
/* ************************************************************************** */

#define ERROR__MISSING \
	"Error: Error: Missing parameters !\n"

#define ERROR__HELP \
	"Try 'help set kernel' for more information.\n"

/* ************************************************************************** */
/*                                                                            */
/* Header implementation                                                      */
/*                                                                            */
/* ************************************************************************** */

int	command__set__kernel(
		const char **tokens,
		t_cl *cl)
{
	if (tokens[0] != NULL)
		return (command__set__kernel__name(tokens, cl));
	ft_putstr_fd(ERROR__MISSING ERROR__HELP, STDERR_FILENO);
	return (EXIT_FAILURE);
}
