FROM ubuntu:18.04
RUN apt-get update -y
RUN apt-get install wget build-essential -y
WORKDIR /opt/
RUN wget https://github.com/sisqo256/Rebelcoin/releases/download/untagged-7fa3fec4d854fc4857ab/Rebelcoin-Linux.tar.gz
RUN tar zxvf Rebelcoin-Linux.tar.gz
RUN mv Rebelcoin/bin/rebelcoin* /usr/bin/
RUN wget https://raw.githubusercontent.com/TheRetroMike/rmt-nomp/master/scripts/blocknotify.c
RUN gcc blocknotify.c -o /usr/bin/blocknotify
CMD /usr/bin/rebelcoind -daemon;tail -f /root/.rebelcoin/debug.log
