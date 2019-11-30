#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
IMG_NAME="audiotest-build"
docker build --tag ${IMG_NAME} "${DIR}"

