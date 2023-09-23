FROM rustlang/rust:nightly-slim

ENV DEBIAN_FRONTEND=noninteractive
ENV VERSION=nightly-2022-11-11

RUN apt-get update -yqq
RUN apt-get install -yqq libclang-dev llvm-dev

RUN rustup install $VERSION
RUN rustup component add --toolchain=$VERSION rust-src rustfmt llvm-tools-preview clippy


RUN apt-get update && \
    apt-get install -y software-properties-common && \
    apt-get update && \
    apt-get install -y git python3 python3-pip python-is-python3 wget && \
    python3 -m pip install pros-cli==3.4.3

RUN mkdir /install-dir && \
    cd /install-dir && \
    wget https://armkeil.blob.core.windows.net/developer/Files/downloads/gnu-rm/9-2020q2/gcc-arm-none-eabi-9-2020-q2-update-x86_64-linux.tar.bz2 --no-check-certificate && \
    tar -xjvf gcc-arm-none-eabi-9-2020-q2-update-x86_64-linux.tar.bz2

ENV PATH "$PATH:/install-dir/gcc-arm-none-eabi-9-2020-q2-update/bin/"


#needed to connect USB devices
# RUN apt install usbip hwdata usbutils



