# Philosophers

Vous trouverez ci-dessous une description du projet Philosophers avec des explications et justifications des choix effectués.

## Introduction

Le sujet du projet est disponible dans le repository git, nous rappelerons seulement ici les spécificités des 3 parties (philo_one, philo_two et philo_three) du projet.

Nous identifierons respectivement les fourchettes et philosophes numéro i par les appellations fork_i et philo_i.

Sur les schémas ci-dessous, un philosophe rassasié est dit "full".

### Philo_one

#### *Spécificités*

- Utilisation de mutex
- Les fourchettes sont situées entre les philosophes (fork_n disponible pour philo_n et philo_n+1)
- Chaque philosophe est géré par un thread

### Philo_two

#### *Spécificités*

- Utilisation de semaphores
- Les fourchettes sont situées au centre de la table (fork_n disponible pour tous les philosophes)
- Chaque philosophe est géré par un thread

### Philo_three

#### *Spécificités*

- Utilisation de semaphores
- Les fourchettes sont situées au centre de la table (fork_n disponible pour tous les philosophes)
- Chaque philosophe est géré par un fork (child process)

## Philo_one

### Structure globale

![schema_0](./images_readme/diagram_philo_one.png)

### Gestion des mutex

Chaque fourchette a son propre mutex qui permet de la verrouiller lorsqu'un philosophe la prend.

On utilise aussi un mutex partagé par tous les philosophes qui permet de print du texte sans mélange.

### Vérification de la mort des philosophes

Le programme "parent" ayant accès aux ressources des threads, c'est lui qui vérifie en permanence en fond si chaque philosophe est encore vivant.

### Spécificités

#### 1. Eviter de se retrouver bloqué

Si chaque philosophe prend en même temps sa fourchette gauche, aucun ne pourra prendre sa fourchette droite.

Pour éviter cette situation :
- Les philosophes paires (0, 2, 4...) commencent par prendre leur fourchette droite, puis leur fourchette gauche.
- Les philosophes impaires font l'inverse.

#### 2. Eviter la mort d'un philosophe

Selon les paramètres utilisés, une fourchette pourrait être utilisée deux fois d'affilée par le même philosophe.

Pour éviter cette situation :
- Chaque fourchette note le numéro du dernier philosophe l'ayant utilisée.
- Un philosophe n4essaye de prendre une fourchette que s'il n'est pas le dernier à l'avoir utilisée.

## Philo_two

### Gestion des semaphores

On utilise un seul semaphore global pour gérer l'ensemble des fourchettes. Sa valeur initiale est le nombre de philosophes.

On utilise aussi un semaphore partagé par tous les philosophes qui permet de print du texte sans mélange. Sa valeur initiale est égale à un.

### Vérification de la mort des philosophes

Le programme "parent" ayant accès aux ressources des threads, c'est lui qui vérifie en permanence en fond si chaque philosophe est encore vivant.

### Spécificités

#### 1. Eviter la mort d'un philosophe

Si aucune précaution n'est prise, certains philosophes pourraient manger deux fois pendant que d'autres attendent leur tour, provoquant leur mort.

Pour éviter cette situation :
- On utilise un entier croissant représentant le prochain philosophe à être autorisé à prendre une fourchette.
- Quand le philosophe en question a pris ses deux fouchettes, on incrémente l'entier (ou on lui donne la valeur de 1 si on était rendu au dernier philosophe).

### Structure globale

La structure globale de Philo_two est la même que celle de Philo_one.

![schema_0](./images_readme/diagram_philo_two.png)

## Philo_three

### Structure globale

![schema_0](./images_readme/diagram_philo_three.png)

### Gestion des semaphores

*Cf même section de Philo_two pour le semaphore des fourchettes et celui de l'écriture.*

Contrairement à Philo_one et Philo_two qui utilisaient des threads, l'utilisation de processus fils ne permet pas :
- Aux childs de modifier une valeur dans le processus parent (pour indiquer qu'un philosophe est mort ou rassasié).
- Au parent de 



### Vérification de la mort des philosophes

Le programme "parent" ayant accès aux ressources des threads, c'est lui qui vérifie en permanence en fond si chaque philosophe est encore vivant.

### Spécificités

#### 1. Eviter la mort d'un philosophe

*Cf même section de Philo_two.*