FROM nginx:1.26.2-alpine

# Install OpenSSL
RUN apk add --no-cache openssl

# Generate develompent SSL certificates
RUN mkdir -p /etc/nginx/ssl && \
openssl req -x509 -nodes -days 365 \
-newkey rsa:2048 \
-keyout /etc/nginx/ssl/nginx-selfsigned.key \
-out /etc/nginx/ssl/nginx-selfsigned.crt \
-subj "/CN=localhost"

# 기본 설정 유지를 위한 conf.d 경로 선택 (안정성)
COPY ./docker/nginx/nginx.conf /etc/nginx/nginx.conf

EXPOSE 80 443

CMD ["nginx", "-g", "daemon off;"]