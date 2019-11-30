#!/usr/bin/env bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
ROOT="$( cd ${DIR}/../.. && pwd )"
IMG_NAME="audiotest-build"
CONTAINER_NAME="audiotest-build"

#cd "${DIR}" &&
docker kill ${CONTAINER_NAME}
docker rm ${CONTAINER_NAME}
cmd="docker run -v ${ROOT}:/root/ --name ${CONTAINER_NAME} ${IMG_NAME}"
echo "${cmd}"
cd "${DIR}" && ${cmd}
