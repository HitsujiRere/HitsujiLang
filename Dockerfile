FROM ubuntu:latest
RUN apt update
RUN apt -y upgrade
RUN apt install -y gcc g++ make sudo
RUN adduser --disabled-password --gecos '' user
RUN echo 'user ALL=(root) NOPASSWD:ALL' > /etc/sudoers.d/user
USER user
WORKDIR /home/user