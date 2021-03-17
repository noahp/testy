FROM ubuntu:focal

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get -y install \
    build-essential \
    cppcheck \
    clang-11 \
    clang-format \
    clang-tidy \
    git \
    python3-pip

# get user id from build arg, so we can have read/write access to directories
# mounted inside the container. only the UID is necessary, UNAME just for
# cosmetics
ARG UID=1010
ARG UNAME=builder

RUN useradd --uid $UID --create-home --user-group ${UNAME} && \
    echo "${UNAME}:${UNAME}" | chpasswd && adduser ${UNAME} sudo

USER ${UNAME}

ENV LANG=C.UTF-8 LC_ALL=C.UTF-8

ENV PATH /home/${UNAME}/.local/bin:$PATH

RUN pip3 install pre-commit==2.11.1

WORKDIR /mnt/workspace
