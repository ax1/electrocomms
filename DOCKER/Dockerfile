FROM node:18-bullseye
RUN apt update
RUN apt install -y git make net-tools
WORKDIR /SOFTWARE
RUN git clone https://github.com/ax1/electrocomms
ENTRYPOINT [ "/bin/bash"]
WORKDIR /SOFTWARE/electrocomms/src
RUN mkdir ../bin
RUN /usr/bin/make
WORKDIR /SOFTWARE/electrocomms/bin
RUN ./electrocomms 8080 > /dev/null 2>&1 &
