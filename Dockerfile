FROM ubuntu:16.04
RUN apt-get update && apt-get install -yq gcc nano
COPY osx/client.c .
COPY osx/fserver.c .
ENTRYPOINT ["/bin/bash"]