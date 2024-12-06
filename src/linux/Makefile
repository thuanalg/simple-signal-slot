target=libsimplelog.so
debugFlag=-g -fPIC -Wall -shared 
releaseFlag=-fPIC -Wall -shared
LIBS+=-lpthread
src=../simplelog/simplelog.c ../simplelog/simplelog.h ../simplelog/simplelog_config.h
INC=-I../
INC+=-I../simplelog
#CFLAGS=-ansi
CFLAGS=-std=gnu89 -DUNIX_LINUX
CPPFLAGS=-std=c++98 -DUNIX_LINUX
signal_slot = ../implement/simple_implement_signal_slot.h ../implement/simple_implement_signal_slot.cpp 
signal_slot += ../implement/simple_signal_slot.h ../implement/simple_signal_slot.cpp 
libtarget_signalslot=libsignalslot.so

debug:
	gcc ${debugFlag} -o ${target} ${src} ${LIBS} ${CFLAGS}
#	gcc -g -o simpplelog_sample  ../c_test/main.c ${src} ${LIBS} ${INC}
	g++ -g -o ${libtarget_signalslot}  ${signal_slot} ${LIBS} ${CPPFLAGS} ${INC} -L./ -lsimplelog
#	g++ -g -o simpplelog_cpp_direct_sample  ../cpp_test/main.cpp ${src} ${LIBS} ${INC} ${CPPFLAGS}

release:
	gcc ${releaseFlag} -o ${target} ${src} ${LIBS} ${CFLAGS}
#	gcc -o simpplelog_sample  ../c_test/main.c ${src} ${LIBS} ${INC}
#	g++ -o simpplelog_cpp_sample  ../cpp_test/main.cpp ${LIBS} ${INC} ${CPPFLAGS} -L./ -lsimplelog
#	g++ -o simpplelog_cpp_direct_sample  ../cpp_test/main.cpp ${src} ${LIBS} ${INC} ${CPPFLAGS}
	g++ -g -o ${libtarget_signalslot}  ${signal_slot} ${LIBS} ${CPPFLAGS} ${INC} -L./ -lsimplelog

clean:
	rm -rf ${target} ${libtarget_signalslot}
#	rm -rf ${target} libsimplelog.so simpplelog_sample simpplelog_cpp_sample simpplelog_cpp_direct_sample
