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

// **** 		THIS FILE IS NOT INCLUDED IN THE PROJECT				****
// **** 	THREADS ARE NOT ALLOWED IN THE EXTERNAL FUNCTIONS LIST		****
// ****				I WANT TO IMPLEMENT THEM MYSELF						****
// **** 		I WILL NOT INCLUDE THIS FILE IN THE MAKEFILE			****

/* #include "../../inc/minirt.h"

int		count_cpu_threads()
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
			pthread_cond_wait(&thread_pool->cond_queue, \
				&thread_pool->mutex_queue);

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
		if (pthread_create(&thread_pool->threads[i], NULL, \
			&start_thread, NULL) != 0)
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

void	init_thread_pool(t_mem *mem, t_ThreadPool *pool)
{
	int		i;

	pool = safe_calloc(1, sizeof(t_ThreadPool), "thread_pool malloc error");
	pool->num_threads = count_cpu_threads();
	pool->threads = safe_calloc(pool->num_threads, sizeof(pthread_t), \
	"threads malloc error");
	pool->task_queue_head = NULL;
	pool->task_queue_tail = NULL;
	pool->shutdown = false;
	pthread_mutex_init(&pool->mutex_queue, NULL);
    pthread_cond_init(&pool->cond_queue, NULL);
	i = 0;
	while (i < pool->num_threads)
	{
		if (pthread_create(&pool->threads[i], NULL, &start_thread, NULL) != 0)
			perror("Failed to create thread");
		printf("thread %d created\n", i);
		i++;
	}
	mem->thread_pool = pool;
}

void	destroy_thread_pool(t_ThreadPool *pool)
{
	int		i;
	t_Task	*task;

	if (pool)
	{
		pthread_mutex_lock(&pool->mutex_queue);
		pool->shutdown = true;
		pthread_cond_broadcast(&pool->cond_queue);
		pthread_mutex_unlock(&pool->mutex_queue);
		i = 0;
		while (i < pool->num_threads)
			pthread_join(pool->threads[i++], NULL);
		while (pool->task_queue_head)
		{
			task = pool->task_queue_head;
			pool->task_queue_head = task->next;
			free(task);
		}
		free(pool->threads);
		pthread_mutex_destroy(&pool->mutex_queue);
		pthread_cond_destroy(&pool->cond_queue);
		free(pool);
	}
}
*/