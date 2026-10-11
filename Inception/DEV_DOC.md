# Developer Documentation

## Prerequisites
- Docker
- Docker Compose
- A Linux virtual machine for the project

## Configuration
- Non-secret values are stored in `srcs/.env`.
- Secret values are stored in `secrets/`.
- Persistent host data is stored under `/home/amabbadi/data/`.

## Build and Launch
- `make up` builds the images and starts the stack.
- `make build` only builds the images.
- `make down` stops the containers.
- `make clean` removes containers and volumes.
- `make fclean` removes containers, volumes, and images.
- `make rmdata` cleans data.
- `make setup-docker` gives perms so you don't have to sudo each time.

## Docker Compose Usage
- The compose file is `srcs/docker-compose.yml`.
- NGINX is the only service exposed to the host on port 443.
- WordPress talks to MariaDB on the private Docker network.

## Data Persistence
- MariaDB data is stored in the named volume mapped to `/home/amabbadi/data/mariadb`.
- WordPress files are stored in the named volume mapped to `/home/amabbadi/data/wordpress`.
- Data remains after container recreation as long as the volumes are kept.