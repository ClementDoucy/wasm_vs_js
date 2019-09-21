all: build rm run

build:
	docker build -t express:latest .

run:
	docker run -d --name wasm_vs_js -p 12000:12000 express:latest

start:
	docker start wasm_vs_js

stop:
	docker stop wasm_vs_js

restart:
	docker restart wasm_vs_js

rm:
	- docker rm -f wasm_vs_js
	- docker rm -f wasm_cont

logs:
	docker logs -f wasm_vs_js

compile:
	cp ./front/quick_sort.c ./wasm
	docker build -t wasm_img:latest ./wasm
	docker run --name wasm_cont wasm_img:latest
	docker cp wasm_cont:/home/tmp/quick_sort_wasm.js ./front/
	docker cp wasm_cont:/home/tmp/quick_sort_wasm.wasm ./front/
	docker rm -f wasm_cont
	rm ./wasm/quick_sort.c

clean:
	- rm front/quick_sort_wasm.js
	- rm front/quick_sort_wasm.wasm

.PHONY: all build run start stop restart rm logs compile