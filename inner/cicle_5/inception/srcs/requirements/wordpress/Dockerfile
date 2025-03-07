FROM alpine:3.18

RUN apk --no-cache add php82 php82-cli php82-json \
    php82-mysqli php82-curl php82-dom php82-exif php82-pecl-imagick \
    php82-pecl-igbinary php82-intl php82-mbstring php82-openssl \
    php82-xml php82-fpm php82-zip php82-phar curl dumb-init \
    && mkdir -p /var/www/html

RUN ln -s /usr/bin/php82 /usr/bin/php

COPY ./tools/entrypoint.sh /usr/local/bin/entrypoint.sh
RUN chmod +x /usr/local/bin/entrypoint.sh

# RUN curl -O https://wordpress.org/latest.tar.gz \
#     && tar -xzvf latest.tar.gz --strip-components=1 \
#     && rm latest.tar.gz

#https://developer.wordpress.org/apis/wp-config-php/
RUN sed -i "s|listen = 127.0.0.1:9000|listen = 9000|g" /etc/php82/php-fpm.d/www.conf

#https://make.wordpress.org/cli/handbook/guides/installing/#recommended-installation
RUN curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar \
    && chmod +x wp-cli.phar \
    && mv wp-cli.phar /usr/local/bin/wp

EXPOSE 9000

ENTRYPOINT ["/usr/bin/dumb-init", "--"]

CMD ["sh", "/usr/local/bin/entrypoint.sh"]