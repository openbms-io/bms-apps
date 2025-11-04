#!/bin/sh
set -e

envsubst '${NEXT_HOST} ${NEXT_PORT}' < /etc/nginx/nginx.conf.template > /etc/nginx/nginx.conf

exec nginx -g 'daemon off;'
