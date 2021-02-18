/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:13:31 by bjacob            #+#    #+#             */
/*   Updated: 2021/02/18 13:48:03 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

# define SUCCESS 0
# define FAILURE 1

# define F_NB_ARG -1
# define F_MALLOC -2
# define F_FORK_CREATE -3
# define F_SEM_CREATE -4
# define F_THREAD_CREATE -5
# define F_THREAD_DETACH -6
# define F_CHILD_KILLED -7

# define EATING 0
# define THINKING 1
# define SLEEPING 2
# define DEAD 3
# define FULL 4

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct		s_fork
{
	int				number;
	sem_t			*private_fork_sem;
}					t_fork;

typedef struct		s_philosopher
{
	int				number;
	int				time_last_meal;
	int				time_start_sleep;
	pthread_t		thread;
	int				*next_philo_eat;
	struct s_game	*game;
}					t_philosopher;

typedef struct		s_game
{
	int				nb_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nb_philo_eat;
	t_philosopher	**philo;
	t_fork			**fork;
	t_list			*ptrs;
	int				start_time;
	sem_t			*print_sem;
	sem_t			*fork_sem;
	sem_t			*end_sem;
	sem_t			*full_sem;
	int				next_philo_eat;
	pid_t			*tab_pid;
}					t_game;

/*
** philo_three.c
*/
void				launch_philo(t_philosopher *philo);
int					create_semaphores(t_game *game);
int					ft_kill_all_child(t_game *game, int nb_childs);

/*
** init_philo_three.c
*/
int					catch_arg(t_game *game, int argc, char **argv);
int					game_init(t_game *game);

/*
** childs.c
*/
int					create_childs(t_game *game);
int					manage_childs(t_game *game);

/*
** philo_utils.c
*/
void				inc_sem_end(t_game *game);
int					print_state(t_philosopher *philo, char *str);
int					get_time(void);
void				*check_dead_philo_background(void *ptr);

/*
** activity.c
*/
int					philo_circle(t_philosopher *philo, int *count);

/*
** nb_utils.c
*/
int					ft_atoi(char *str);
char				*ft_itoa(int n);

/*
** str_utils.c
*/
char				*create_fork_name(t_game *game, char *str, int number);

/*
** lst_utils.c
*/
t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void *));

/*
** clear_objects.c
*/
void				*add_lst_to_free(t_game *game, void *ptr);
void				*malloc_lst(t_game *game, int size);
int					clear_all_semaphores(t_game *game,
										int nb_fork_created);
int					free_all_ptr(t_game *game);
void				ft_exit(t_game *game);

/*
** errors.c
*/
int					print_error(sem_t *print_sem, int error);
int					ft_error(t_game *game, void *ptr, int error,
							int nb_fork_created);

#endif
