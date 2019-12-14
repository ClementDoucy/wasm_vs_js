FROM webassembly/toolchain:latest
WORKDIR /home/tmp/
ADD ./quick_sort.c .
CMD ["emcc", \
     "quick_sort.c", \
     "-o", \
     "quick_sort_wasm.js", \
     "-s", \
     "EXPORTED_FUNCTIONS=['_launch_sort']", \
     "-s", \
     "EXTRA_EXPORTED_RUNTIME_METHODS=['cwrap']"]