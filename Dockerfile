FROM ubuntu:22.04

ARG UID
ARG GID

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    curl \
    zip \
    git

# Install Python 3.11
RUN apt-get install build-essential software-properties-common -y && \
    add-apt-repository ppa:deadsnakes/ppa && \
    apt-get update && \
    apt install python3.11 -y

# Silence CMake warrning "Cannot create package registry file"
RUN mkdir -p /.cmake && chmod 777 /.cmake

# Install CMake
RUN curl -sSL https://cmake.org/files/v3.24/cmake-3.24.4-linux-x86_64.tar.gz | tar --strip-component=1 -xzC /usr/local

# Creating build directory to avoid CMake Error: Unable to (re)create the private pkgRedirects directory
RUN mkdir -p /workspace/build && chmod 777 /workspace/build

RUN groupadd -g ${GID} dev_user
RUN useradd -m -u ${UID} -g ${GID} -s /bin/bash dev_usr

COPY /scripts/build_and_run_docker_container.py /
RUN chmod 765 /build_and_run_docker_container.py

ENTRYPOINT [ "/build_and_run_docker_container.py" ]
