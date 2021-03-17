#!/usr/bin/env bash

# Simple test script to run the tests in docker

# Error on any non-zero command, and print the commands as they're run
set -ex

# Make sure we have the docker utility
if ! command -v docker; then
    echo "🐋 Please install docker first 🐋"
    exit 1
fi

# Set the docker image name to default to repo basename
DOCKER_IMAGE_NAME=${DOCKER_IMAGE_NAME:-$(basename -s .git "$(git remote --verbose | awk 'NR==1 { print tolower($2) }')")}

# build the docker image
DOCKER_BUILDKIT=1 docker build -t "$DOCKER_IMAGE_NAME" --build-arg "UID=$(id -u)" -f Dockerfile .

docker run --rm -v "$(pwd)":/mnt/workspace -t "$DOCKER_IMAGE_NAME" bash -c "
# commit checker
pre-commit run --all-files
# basic happy path example
make -C example
# check clang-11
CC=clang-11 make -C example
# this test should fail
! make -C example-failing"
