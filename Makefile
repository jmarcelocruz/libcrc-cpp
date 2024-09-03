sources := libcrc/libcrc/crc.cpp \
           libcrc/libcrc/crc.test.cpp
depends := $(patsubst %.cpp,%.d,${sources})
objects := $(patsubst %.cpp,%.o,${sources})

includedirs := libcrc

binaries := libcrc.a \
            libcrc/libcrc/crc_test

CXXFLAGS := -std=c++17 $(addprefix -I,${includedirs})
LDFLAGS :=
TEST_LDFLAGS := -lgtest -lgtest_main

DESTDIR :=
INSTALL := install

prefix := /usr/local
exec_prefix := ${prefix}
includedir := ${prefix}/include
libdir := ${exec_prefix}/lib

install: libcrc.a $(shell find ${includedirs} -type f -name '*.hpp')
	${INSTALL} -m 755 -d ${DESTDIR}${includedir}
	${INSTALL} -m 755 -d ${DESTDIR}${libdir}
	${INSTALL} -m 755 $< ${DESTDIR}${libdir}
	find ${includedirs} -type f -name '*.hpp' | xargs -I % ${INSTALL} -m 644 -D % ${DESTDIR}${includedir}/%

uninstall:
	rm -f ${DESTDIR}${libdir}/libcrc.a
	find ${includedirs} -type f -name '*.hpp' | xargs -I % rm -f ${DESTDIR}${includedir}/%

libcrc.a: libcrc/libcrc/crc.o
	${AR} rcs $@ $^

libcrc/libcrc/crc_test: libcrc/libcrc/crc.test.o libcrc/libcrc/crc.o
	${CXX} $^ ${LDFLAGS} ${TEST_LDFLAGS} -o $@

${objects}: %.o: %.cpp
	${CXX} -c $< ${CXXFLAGS} -o $@

${depends}: %.d: %.cpp
	${CXX} $^ ${CXXFLAGS} -MM -MT $(patsubst %.cpp,%.o,$<) -o $@

clean:
	rm -f ${binaries} ${depends} ${objects}

.PHONY: clean

-include ${depends}
