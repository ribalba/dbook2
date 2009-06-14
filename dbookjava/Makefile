CC=gcc
JC=javac
JH=javah
JLIB=/usr/lib/jvm/java-6-sun-1.6.0.07/include 
JLIBARCH=/usr/lib/jvm/java-6-sun-1.6.0.07/include/linux 

all:
	${JC} dbookjava.java
	${JH} dbookjava
	${CC} -c -I${JLIB} -I${JLIBARCH} -o dbookjava.o dbookjava.c
	${CC} -shared -o libdbookjava.so dbookjava.o

clean: 
	rm dbookjava.class dbookjava.o libdbookjava.so dbookjava.h
