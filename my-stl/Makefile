COMPILER=clang
CFLAGS=-Wall
CXXVERSION=c++20

stackbench: stack.o stack-base-test.o seqlist.o
	${COMPILER} ${CFLAGS} -std=${CXXVERSION} stack.o stack-base-test.o seqlist.o -o $@

stack-base-test.o: ./test-case/stack-base-test.cpp
	${COMPILER} ${CFLAGS} -std=${CXXVERSION} -c $< -o $@

seqlist.o: ./abstract-data-structure/seqlist.cpp ./abstract-data-structure/seqlist.h
	${COMPILER} ${CFLAGS} -std=${CXXVERSION} -c $< -o $@

# 通用配置
%.o: %.cpp %.h
	${COMPILER} ${CFLAGS} -std=${CXXVERSION} -c $< -o $@

clean:
	rm -f stackbench *.o