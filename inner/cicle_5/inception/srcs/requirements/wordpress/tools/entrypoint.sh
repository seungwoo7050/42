#!/bin/sh
# https://make.wordpress.org/cli/handbook/how-to/how-to-install/

# WordPress 설정 파일이 존재하지 않는 경우 초기화 수행
if [ ! -e "/var/www/html/wp-config.php" ]; then
    cd /var/www/html

    wp core download --allow-root
    wp config create --dbname=$MYSQL_DATABASE --dbuser=$MYSQL_USER --dbpass=$MYSQL_PASSWORD --dbhost=$DB_HOST
    wp core install --url=$DOMAIN_NAME --title=$WP_NAME --admin_user=$WP_ADMIN_USER --admin_password=$WP_ADMIN_PASSWORD --admin_email=$WP_ADMIN_EMAIL
    wp user create $WP_USER $WP_USER_EMAIL --user_pass=$WP_USER_PASSWORD
fi

/usr/sbin/php-fpm82 -F