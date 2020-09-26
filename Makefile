gpuclocks: gpuclocks.c
	gcc -o gpuclocks gpuclocks.c

install:
	cp gpuclocks /usr/bin/
	chmod u+s /usr/bin/gpuclocks

clean:
	rm gpuclocks
