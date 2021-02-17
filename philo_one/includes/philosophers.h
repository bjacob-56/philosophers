/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:12:44 by bjacob            #+#    #+#             */
/*   Updated: 2021/02/17 15:52:04 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define SUCCESS 0
# define FAILURE 1

# define F_NB_ARG -1
# define F_MALLOC -2
# define F_THREAD_CREATE -3
# define F_THREAD_DETACH -4
# define F_THREAD_JOIN -5
# define F_MUTEX_CREATE -6

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
	pthread_mutex_t mutex;
	int				last_philo;
}					t_fork;

typedef struct		s_philosopher
{
	int				number;
	int				state;
	int				time_last_meal;
	int				time_start_sleep;
	t_fork			*fork_l;
	t_fork			*fork_r;
	pthread_t		thread;
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
	pthread_mutex_t print_mutex;
	int				is_over;
}					t_game;

/*
** init_philo_one.c
*/
int					catch_arg(t_game *game, int argc, char **argv);
int					game_init(t_game *game);

/*
** philo_utils.c
*/
int					print_state_full(t_philosopher *philo);
int					print_state(t_philosopher *philo, char *str);
int					get_time(void);
int					check_dead(int time, t_philosopher *philo);
int					check_all_philo_dead(t_game *game);

/*
** activity.c
*/
int					philo_circle(t_philosopher *philo, int *count);

/*
** nb_utils.c
*/
int					ft_atoi(char *str);

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
int					free_all_ptr(t_game *game);
int					clear_all_mutex(t_game *game, int nb_fork_created);
void				ft_exit(t_game *game);

/*
** errors.c
*/
int					print_error(t_game *game, int error);
int					ft_error(t_game *game, void *ptr, int error,
							int nb_fork_created);

#endif
