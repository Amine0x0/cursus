FROM debian:12

RUN apt-get update && apt-get install -y nginx openssl && rm -rf /var/lib/apt/lists/*

RUN mkdir -p /etc/nginx/certs /run/nginx && \
	openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
	-keyout /etc/nginx/certs/incep.key \
	-out /etc/nginx/certs/incep.crt \
	-subj "/C=MA/ST=KHOURIBGA/L=KHOURIBGA/O=1337/OU=STUDENT/CN=amabbadi.42.fr"

COPY conf/default.conf /etc/nginx/conf.d/default.conf

ENTRYPOINT ["nginx", "-g", "daemon off;"]