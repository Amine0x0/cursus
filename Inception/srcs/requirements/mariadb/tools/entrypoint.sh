#!/bin/sh

set -eu

mkdir -p /run/mysqld
chown -R mysql:mysql /run/mysqld /var/lib/mysql

MYSQL_PASSWORD=$(cat "$MYSQL_PASSWORD_FILE")
MYSQL_ROOT_PASSWORD=$(cat "$MYSQL_ROOT_PASSWORD_FILE")

if [ ! -d /var/lib/mysql/mysql ]; then
    mariadb-install-db --user=mysql --datadir=/var/lib/mysql >/dev/null
fi

mariadbd --user=mysql --skip-networking --socket=/run/mysqld/mysqld.sock &
temp_server=$!

until mariadb-admin --socket=/run/mysqld/mysqld.sock ping >/dev/null 2>&1; do
    sleep 1
done

mariadb --socket=/run/mysqld/mysqld.sock -uroot -p"$MYSQL_ROOT_PASSWORD" <<EOF
ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';
CREATE DATABASE IF NOT EXISTS ${MYSQL_DATABASE};
CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';
GRANT ALL PRIVILEGES ON ${MYSQL_DATABASE}.* TO '${MYSQL_USER}'@'%';
FLUSH PRIVILEGES;
EOF

kill "$temp_server"
wait "$temp_server" 2>/dev/null || true

exec mariadbd --user=mysql --bind-address=0.0.0.0