FROM debian:8 AS build

# Install & clean
RUN apt-get update \
&& apt-get install -y gcc make \
&& apt-get clean

# Add sources
COPY Makefile /app/
COPY ./src /app/src/
COPY ./include /app/include/

# Define PWD
WORKDIR /app/

# Build
RUN make .PHONY

# Start
#ENTRYPOINT ["bash"]

FROM debian:8

RUN apt-get update \ 
&& apt-get install -y gcc

WORKDIR /root/

COPY --from=build /app/libmy_malloc_Linux.so .
COPY tests/ .

#ENTRYPOINT ["sh", "launch_test.sh"]

### DEBUG ### 
ENTRYPOINT ["bash"]
