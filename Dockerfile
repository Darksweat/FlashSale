FROM gcc:latest

RUN  mkdir /usr/src/workspace

WORKDIR /usr/src/workspace

RUN  mkdir bazel

COPY bazel/bazel-0.21.0-installer-linux-x86_64.sh /usr/src/workspace/bazel

COPY test.cc /usr/src/workspace

RUN  mkdir grpc

COPY grpc /usr/src/workspace/grpc

COPY mysql-8.0.13-linux-glibc2.12-x86_64/lib /usr/src/workspace/mysql

RUN  gcc test.cc

CMD ["./a.out"]