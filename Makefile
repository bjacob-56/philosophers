all:
	@echo "---- \033[36m Makefile philo_one \033[0m ----"
	@$(MAKE) -C ./philo_one
	@echo "---- \033[36m Makefile philo_two \033[0m ----"
	@$(MAKE) -C ./philo_two
	@echo "---- \033[36m Makefile philo_three \033[0m ----"
	@$(MAKE) -C ./philo_three

clean:
	@echo "---- \033[36m Clean philo_one \033[0m ----"
	@$(MAKE) clean -C ./philo_one
	@echo "---- \033[36m Clean philo_two \033[0m ----"
	@$(MAKE) clean -C ./philo_two
	@echo "---- \033[36m Clean philo_three \033[0m ----"
	@$(MAKE) clean -C ./philo_three

fclean:
	@echo "---- \033[36m Fclean philo_one \033[0m ----"
	@$(MAKE) fclean -C ./philo_one
	@echo "---- \033[36m Fclean philo_two \033[0m ----"
	@$(MAKE) fclean -C ./philo_two
	@echo "---- \033[36m Fclean philo_three \033[0m ----"
	@$(MAKE) fclean -C ./philo_three

re:
	@echo "---- \033[36m Re philo_one \033[0m ----"
	@$(MAKE) re -C ./philo_one
	@echo "---- \033[36m Re philo_two \033[0m ----"
	@$(MAKE) re -C ./philo_two
	@echo "---- \033[36m Re philo_three \033[0m ----"
	@$(MAKE) re -C ./philo_three