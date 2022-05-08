# See here for image contents: https://github.com/microsoft/vscode-dev-containers/tree/v0.231.6/containers/cpp/.devcontainer/base.Dockerfile

ARG VARIANT="ubuntu-18.04"
FROM mcr.microsoft.com/vscode/devcontainers/cpp:0-${VARIANT}

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends doxygen graphviz
