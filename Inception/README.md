*This project has been created as part of the 42 curriculum by amabbadi.*

## Description
This project sets up a small Docker based infrastructure with NGINX, WordPress, and MariaDb, the goal of this project is to simulate the LEMP stack and how to orchestrate all of it's services.
The goal is to serve WordPress over HTTPS, keep data persistent with named volumes, and manage the services with Docker Compose.

## Instructions
Run `make setup-docker` to give perms to the user to avoid redundant sudo calls.
Run `make up` to build and start the stack.
Run `make down` to stop it.
Run `make clean` to remove containers and volumes.
Run `make fclean` to remove containers, volumes, and images.

Access the website at `https://amabbadi.42.fr` and the WordPress admin panel at `https://amabbadi.42.fr/wp-admin`.

## Resources
- Docker documentation
- Some docker books snippets.
- Docker Compose documentation
- WordPress docs either from dockerhub or some examples.
- MariaDB documentation same as above.
- NGINX documentation same as above.

AI was mostly used to direct me towards the right ressources to learn with some minor debuggins.

## Project Description
Docker is used to isolate services into separate containers so each one has its own responsibility.
Compared to virtual machines, Docker is lighter and faster because it shares the host kernel.

Secrets are stored in files under `secrets/` instead of being hardcoded in Dockerfiles.
Environment variables in `srcs/.env` are used for non-secret configuration values.

Docker networks let the containers communicate privately without exposing internal ports to the host.
Docker volumes are used for persistence, while bind mounts are not used for application storage.
The services included in this project are NGINX, WordPress with php-fpm, and MariaDB.