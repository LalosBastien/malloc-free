== Dependencies ==
- Docker : https://docs.docker.com/engine/installation/

== How to use ==

build
- docker build -t imagename .

run
- docker run  -ti imagename

== Important ==
- Modify only files in src/ and include/
- Can access to container with this command : docker run -ti --entrypoint="bash" imagename
- All .c must be in the root of src/
- All .h must be in the root of include/