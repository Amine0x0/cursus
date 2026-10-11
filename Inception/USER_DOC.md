# User Documentation

## Services Provided
- NGINX serves the website over HTTPS.
- WordPress provides the public website and the administration dashboard.
- MariaDB stores the WordPress data.

## Start and Stop
- Start the stack with `make up`.
- Stop the stack with `make down`.

## Access
- Website: `https://amabbadi.42.fr`
- Administration dashboard: `https://amabbadi.42.fr/wp-admin`

## Credentials
- WordPress admin username: `supervisor`
- WordPress admin password: stored in `secrets/credentials.txt`
- WordPress database user password: stored in `secrets/db_password.txt`
- MariaDB root password: stored in `secrets/db_root_password.txt`

## Basic Checks
- Use `docker compose ps` to verify that the three services are running.
- Use `docker volume ls` to verify persistent volumes exist.
- If the site does not load, check the containers with `docker compose logs`.