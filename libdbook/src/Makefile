LIB_VERSION = 0.1

libdbook:
	gcc -Wall -fPIC -c -shared libdbook.c
	gcc ${LDFLAGS} -shared -o libdbook.so.${LIB_VERSION} libdbook.o
	ar rc libdbook.a libdbook.o
	ranlib libdbook.a

clean:
	rm libdbook.o  libdbook.so.${LIB_VERSION} libdbook.a
