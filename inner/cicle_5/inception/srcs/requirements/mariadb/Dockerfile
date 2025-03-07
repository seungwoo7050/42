FROM alpine:3.18

RUN apk add --no-cache mariadb mariadb-client dumb-init

COPY ./tools/entrypoint.sh /usr/local/bin/entrypoint.sh
COPY ./conf/my.cnf /etc/my.cnf

RUN chmod +x /usr/local/bin/entrypoint.sh

EXPOSE 3306

ENTRYPOINT ["/usr/bin/dumb-init", "--"]

CMD [ "sh", "/usr/local/bin/entrypoint.sh" ]
