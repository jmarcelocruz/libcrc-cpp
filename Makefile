sources :=
depends := $(patsubst %.cpp,%.d,${sources})
objects := $(patsubst %.cpp,%.o,${sources})

includedirs :=

binaries :=

CXXFLAGS := -std=c++17 $(addprefix -I,${includedirs})
LDFLAGS :=

libcrc.a:
	${AR} rcs $@ $^

${objects}: %.o: %.cpp
	${CXX} -c $< ${CXXFLAGS} -o $@

${depends}: %.d: %.cpp
	${CXX} $^ -MM -MT $(patsubst %.cpp,%.o,$<) -o $@

clean:
	rm -f ${binaries} ${depends} ${objects}

.PHONY: clean

-include ${depends}
