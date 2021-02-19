# Philosophers

Vous trouverez ci-dessous une description du projet Philosophers avec des explications et justifications des choix effectués.

## Introduction

Le sujet du projet est disponible dans le repository git, nous rappelerons seulement ici les spécificités des 3 parties (philo_one, philo_two et philo_three) du projet.

Nous identifierons respectivement les fourchettes et philosophes numéro i par les appellations fork_i et philo_i.

### Philo_one

#### *Spécificités*

	* Utilisation de mutex
	* Les fourchettes sont situées entre les philosophes (fork_n disponible pour philo_n et philo_n+1)
	* Chaque philosophe est géré par un thread

### Philo_two

#### *Spécificités*

	* Utilisation de semaphores
	* Les fourchettes sont situées au centre de la table (fork_n disponible pour tous les philosophes)
	* Chaque philosophe est géré par un thread

### Philo_three

#### *Spécificités*

	* Utilisation de semaphores
	* Les fourchettes sont situées au centre de la table (fork_n disponible pour tous les philosophes)
	* Chaque philosophe est géré par un fork (child process)

