FROM ubuntu:18.04
RUN apt-get update -y
RUN apt-get install wget build-essential -y
WORKDIR /opt/
RUN wget https://github.com/sisqo256/rebelcoin.git
RUN mv rebelcoin/bin/rebelcoin* /usr/bin/
RUN wget https://raw.githubusercontent.com/sisqo256/rmt-nomp/master/scripts/blocknotify.c
RUN gcc blocknotify.c -o /usr/bin/blocknotify
CMD /usr/bin/rebelcoind -daemon;tail -f /root/.rebelcoin/debug.log