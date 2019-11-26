
# malloc-free
Malloc & Free implementation in language C using docker for generate debian stress test environment.

### Dependencies ###
- Docker : https://docs.docker.com/engine/installation/

### Important ###
- Modify only files in src/ and include/
- Can access to container with this command : docker run -ti --entrypoint="bash" ${imagename}
- All .c must be in the root of src/
- All .h must be in the root of include/

### How to use ###
It is very simple
- Construct docker image & run it :
```shell
docker build -t munchks/malloc-free .
docker run -ti munchks/malloc-free
```
- Choose the test you want to execute
```html
________________________
< Let's stress a bit my malloc >
 ------------------------
      \                _
       \              (_)
        \   ^__^       / \
         \  (oo)\_____/_\ \
            (__)\       ) /
                ||----w ((
                ||     ||>>


  1  == Simple allocation test == 
  2  == Allocate all memory in a big chunk ==
  3  == Free list coalescing test ==
  4  == Stress test ==
  5  == Stress test with particular seed ==

  ~>
```

### Informations ###

Design pattern used : `First-Fit`.
Consist to search the first block that match the requested memory size to
aggregates free memory by scanning the entire region on request or when an allocation request does not find sufficient free memory.

Pros :
- Fast & Simple
- Low overhead
- It fits general purpose

Cons :
- Does not have a strategy to avoid memory fragmentation,
- Does not implement a time deterministic strategy to find a free memory block.
- Does not have protection or detection against memory boundary overwrites.
