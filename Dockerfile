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
RUN curl -sSL https://cmake.org/files/v3.29/cmake-3.29.0-rc2-linux-x86_64.tar.gz | tar --strip-component=1 -xzC /usr/local

# Creating build directory to avoid CMake Error: Unable to (re)create the private pkgRedirects directory
RUN mkdir -p /workspace/build && chmod 777 /workspace/build

RUN groupadd -g ${GID} dev_user
RUN useradd -m -u ${UID} -g ${GID} -s /bin/bash dev_usr

COPY /scripts/docker/compile_and_execute_unit_tests.py /
RUN chmod 765 /compile_and_execute_unit_tests.py

ENTRYPOINT [ "/compile_and_execute_unit_tests.py" ]
