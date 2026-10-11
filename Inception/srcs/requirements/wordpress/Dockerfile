FROM debian:12

RUN apt-get update -y && apt-get install -y \
	curl \
	php \
	php-fpm \
	php-mysql \
	default-mysql-client \
	&& rm -rf /var/lib/apt/lists/*

RUN curl -fsSL https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar -o /usr/local/bin/wp \
	&& chmod +x /usr/local/bin/wp

RUN mkdir -p /run/php /var/www/html
RUN chown -R www-data:www-data /var/www/html
RUN sed -i 's|listen = .*|listen = 9000|' /etc/php/*/fpm/pool.d/www.conf

COPY ./tools/entrypoint.sh /app/entrypoint.sh
RUN chmod +x /app/entrypoint.sh

ENTRYPOINT ["/app/entrypoint.sh"]