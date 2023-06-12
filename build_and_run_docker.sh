#/!bin/bash

docker_command="/bin/bash"

docker build --tag containers-docker --build-arg UID=$(id -u) --build-arg GID=$(id -g) .
docker run --user $(id -u):$(id -g) --rm --volume $(pwd):/workspace/containers:rw containers-docker ${docker_command}
