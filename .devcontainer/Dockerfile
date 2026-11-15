FROM mcr.microsoft.com/devcontainers/base:ubuntu-24.04

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
        qemu-system-arm \
        gcc-arm-none-eabi \
        libnewlib-arm-none-eabi \
        gdb-multiarch \
        cmake \
        ninja-build \
        make \
        git \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*
