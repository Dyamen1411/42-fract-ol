/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chose_new_kernel.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 00:01:21 by amassias          #+#    #+#             */
/*   Updated: 2023/12/20 00:01:29 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_command_line_internal.h"

int	chose_new_kernel(
		t_cl *cl)
{
	static char	input_buffer[512 + 1] = {0};
	size_t		i;
	ssize_t		n;
	int			t;
	t_kernel	*kernel;

	ft_printf("Chose one of the available kernels :\n");
	i = 0;
	while (i < cl->kernel_count)
	{
		ft_printf("\t* %s\n", cl->kernels[i].name);
		++i;
	}
	t = 0;
	kernel = NULL;
	while (kernel == NULL)
	{
		if (t == 1)
			ft_printf("Unknown kernel name \"%s\".\n", input_buffer);
		ft_printf("> ");
		n = read(STDIN_FILENO, input_buffer, 512);
		if (n < 0)
			return (EXIT_FAILURE);
		if (n == 0)
			return (EXIT_SUCCESS);
		if (input_buffer[n - 1] == '\n')
			--n;
		else
			ft_putchar('\n');
		input_buffer[n] = '\0';
		i = 0;
		while (i < cl->kernel_count)
		{
			if (ft_strcmp(input_buffer, cl->kernels[i].name) == 0)
			{
				kernel = &cl->kernels[i];
				break ;
			}
			++i;
		}
		t = 1;
	}
	i = 0;
	clSetKernelArg(kernel->kernel, 0, sizeof(cl_mem), &cl->cl_screen);
	while (i < kernel->arg_count)
		if (change_param(kernel, i++))
			return (EXIT_FAILURE);
	cl->current_kernel = kernel;
	return (EXIT_SUCCESS);
}
