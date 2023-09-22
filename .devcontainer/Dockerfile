FROM rustlang/rust:nightly-slim

ENV DEBIAN_FRONTEND=noninteractive
ENV VERSION=nightly-2022-11-11

RUN apt-get update -yqq
RUN apt-get install -yqq libclang-dev llvm-dev gcc-arm-none-eabi

RUN rustup install $VERSION
RUN rustup component add --toolchain=$VERSION rust-src rustfmt llvm-tools-preview clippy


RUN apt-get update && \
    apt-get install -y software-properties-common && \
    apt-get update && \
    apt-get install -y git python3 python3-pip python-is-python3 wget && \
    python3 -m pip install pros-cli




