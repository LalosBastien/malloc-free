FROM debian:8 AS build

# Install & clean
RUN apt-get update \
&& apt-get install -y gcc make \
&& apt-get clean

# Add sources
COPY ./src /app/

# Define PWD
WORKDIR /app/

# Build
RUN make

# Start
#ENTRYPOINT ["./libmy_malloc"]


FROM debian:8

WORKDIR /root/

COPY --from=build /app/libmy_malloc .

CMD ["./libmy_malloc"]
