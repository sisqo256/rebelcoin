FROM node:10.19.0-buster
RUN apt-get update
RUN apt-get install -y sudo git nano curl

WORKDIR /opt/
RUN git clone https://github.com/TheRetroMike/rmt-nomp

WORKDIR /opt/rmt-nomp
RUN npm update
RUN rm -rf pool_configs
RUN rm -rf coins
RUN rm config_example.json

RUN ln -s /opt/config/config.json /opt/rmt-nomp/config.json
RUN ln -s /opt/config/pool_configs /opt/rmt-nomp/pool_configs
RUN ln -s /opt/config/coins /opt/rmt-nomp/coins

RUN apt-get install -y redis-server

CMD service redis-server restart; node init.js
