ARG BASE_IMAGE=ghcr.io/pavlozt/firebird-legacy-docker:2.5.9-ss
FROM ${BASE_IMAGE} AS builder

RUN apt-get update && \
    apt-get install -y --no-install-recommends build-essential

WORKDIR /src
COPY src/ .

RUN gcc -c -O -fpic -I/usr/local/firebird/include ibu.c && \
    ld -G ibu.o -lm -lc -L/usr/local/firebird/lib -lib_util -o ibu.so

FROM ${BASE_IMAGE}

COPY --from=builder /src/ibu.so /usr/local/firebird/UDF/

