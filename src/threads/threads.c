/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tday <tday@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 21:43:47 by tday              #+#    #+#             */
/*   Updated: 2025/01/06 21:44:00 by tday             ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/minirt.h"

int		count_threads()
{
	int		num_threads;

	num_threads = sysconf(_SC_NPROCESSORS_ONLN);
	return (num_threads);
}

void	submit_task(t_ThreadPool *thread_pool, t_Task task)
{
	pthread_mutex_lock(&thread_pool->mutex_queue);
	thread_pool->task_queue[thread_pool->task_count] = task;
	thread_pool->task_count++;
	pthread_mutex_unlock(&thread_pool->mutex_queue);
	pthread_cond_signal(&thread_pool->cond_queue);
}
void	execute_task(t_Task *task)
{
	task->function(task->argument);
}

void	start_thread(t_ThreadPool *thread_pool)
{
	t_Task	task;
	int		i;

	while (1)
	{
		pthread_mutex_lock(&thread_pool->mutex_queue);
		while (thread_pool->task_count == 0)
			pthread_cond_wait(&thread_pool->cond_queue, &thread_pool->mutex_queue);

		task = thread_pool->task_queue[0];
		i = 0;
		while (i < thread_pool->task_count - 1)
		{
			thread_pool->task_queue[i] = thread_pool->task_queue[i + 1];
			i++;
		}
		thread_pool->task_count--;

		pthread_mutex_unlock(&thread_pool->mutex_queue);
		execute_task(&task);
	}
}

void	init_threads(t_ThreadPool *thread_pool)
{

	int			i;

	pthread_mutex_init(&thread_pool->mutex_queue, NULL);
	pthread_cond_init(&thread_pool->cond_queue, NULL);
	i = 0;
	while (i < thread_pool->num_threads)
	{
		if (pthread_create(&thread_pool->threads[i], NULL, &start_thread, NULL) != 0)
			perror("Failed to create thread");
		i++;
	}
	i = 0;
	while (i < thread_pool->num_threads)
	{
		if (pthread_join(thread_pool->threads[i], NULL) != 0)
			perror("Failed to join thread");
		i++;
	}
	pthread_mutex_destroy(&thread_pool->mutex_queue);
	pthread_cond_destroy(&thread_pool->cond_queue);
}

