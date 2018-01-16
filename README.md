== Dependencies ==
- Docker : https://docs.docker.com/engine/installation/

== How to use ==

build
- docker build -t imagename .

run
- docker run imagename arg1 arg2 arg3 argN

== Important ==
- Modify only files in src/
- Can access to container with this command : docker run -ti --entrypoint="bash" imagename
- All .c must be in the root of src/
