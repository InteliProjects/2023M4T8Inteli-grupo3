FROM nginx:bullseye

COPY ./conf/default.conf /etc/nginx/conf.d/default.conf
COPY ./sensitive/dotnemo.crt /dotnemo.crt
COPY ./sensitive/dotnemo.key /dotnemo.key
COPY ./sensitive/dotnemo.ca-bundle /dotnemo.ca-bundle