libdbook:
	gcc -Wall -fPIC -c -shared libdbook.c
	gcc ${LDFLAGS} -shared -o libdbook.so.0.1 libdbook.o

clean:
	rm libdbook.o  libdbook.so.0.1
