-include srcs/.env

DOCKER_COMPOSE_FILE = ./srcs/docker-compose.yml
ENV_FILE = ./srcs/.env
DATA_DIR = /home/$(LOGIN)/data
COMPOSE = docker compose --env-file $(ENV_FILE) -f $(DOCKER_COMPOSE_FILE)

all: up

up:
	@mkdir -p $(DATA_DIR)/wordpress $(DATA_DIR)/mariadb
	@$(COMPOSE) up --build -d

build:
	@$(COMPOSE) build

down:
	@$(COMPOSE) down

clean:
	@$(COMPOSE) down -v

fclean: rmdata
	@$(COMPOSE) down -v --rmi all
	@docker system prune -af

rmdata:
	@sudo rm -rf $(DATA_DIR)/wordpress $(DATA_DIR)/mariadb

re: fclean all

hosts_setup:
	@if ! grep -q "$(DOMAIN_NAME)" /etc/hosts; then \
		echo "127.0.0.1 $(DOMAIN_NAME) www.$(DOMAIN_NAME)" | sudo tee -a /etc/hosts > /dev/null; \
	else \
		echo "Host entry already exists."; \
	fi

.PHONY: all up build down clean fclean rmdata re hosts_setup