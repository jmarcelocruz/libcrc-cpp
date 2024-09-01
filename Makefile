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
