#!/bin/sh
set -e

envsubst '${NEXT_HOST} ${NEXT_PORT} ${BUILDING_SEMANTICS_HOST} ${BUILDING_SEMANTICS_PORT}' < /etc/nginx/nginx.conf.template > /etc/nginx/nginx.conf

exec nginx -g 'daemon off;'
