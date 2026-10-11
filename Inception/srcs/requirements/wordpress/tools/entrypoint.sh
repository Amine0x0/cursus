#!/bin/sh

set -eu

MYSQL_PASS=$(cat /run/secrets/db_password)
WP_ADMIN_PASS=$(cat /run/secrets/credentials)
WP_USER_PASS=$(cat /run/secrets/credentials)

mkdir -p /run/php /var/www/html

until mariadb -h mariadb -u"$MYSQL_USER" -p"$MYSQL_PASS" -e "SELECT 1" >/dev/null 2>&1; do
    echo "Still waiting for mariadb..."
    sleep 2
done

cd /var/www/html

if [ ! -f wp-config.php ]; then
    wp core download --allow-root

    wp config create \
        --allow-root \
        --force \
        --dbname="$MYSQL_DATABASE" \
        --dbuser="$MYSQL_USER" \
        --dbpass="$MYSQL_PASS" \
        --dbhost="mariadb"

    wp core install \
        --allow-root \
        --url="https://$DOMAIN_NAME" \
        --title="$WP_SITE_TITLE" \
        --admin_user="$WP_ADMIN_USER" \
        --admin_password="$WP_ADMIN_PASS" \
        --admin_email="$WP_ADMIN_EMAIL"

    wp user create "$WP_USER" "$WP_USER_EMAIL" \
        --role=subscriber \
        --user_pass="$WP_USER_PASS" \
        --allow-root
fi

exec /usr/sbin/php-fpm8.2 -F