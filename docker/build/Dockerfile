FROM alpine:edge

RUN apk update \
    && apk add \
    bash \
    "cmake>3.15" \
    git

#CMD cd /root && cmake .
CMD (cd /root && cmake .) || tail -f /dev/null