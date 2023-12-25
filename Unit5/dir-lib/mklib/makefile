.PHONY:all
all:libhello.so libhello.a

libhello.so:mymath_d.o myprint_d.o
	gcc -shared myprint_d.o mymath_d.o -o libhello.so
mymath_d.o:mymath.c
	gcc -fPIC -c mymath.c -o mymath_d.o
myprint_d.o:myprint.c
	gcc -fPIC -c myprint.c -o myprint_d.o

libhello.a:mymath.o myprint.o
	ar -rc libhello.a mymath.o myprint.o
mymath.o:mymath.c
	gcc -c mymath.c -o mymath.o
myprint.o:myprint.c
	gcc -c myprint.c -o myprint.o

.PHONY:hello
hello:
	mkdir -p hello/lib
	mkdir -p hello/include
	cp -rf *.h hello/include
	cp -rf *.a hello/lib
	cp -rf *.so hello/lib

.PHONY:clean
clean:
	rm -f *.o libhello.a libhello.so
	rm -rf hello


# libhello.a:mymath.o myprint.o
# 	ar -rc libhello.a mymath.o myprint.o
# mymath.o:mymath.c
# 	gcc -c mymath.c -o mymath.o
# myprint.o:myprint.c
# 	gcc -c myprint.c -o myprint.o
# .PHONY:clean
# clean:
# 	rm -f *.o libhello.a