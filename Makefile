CC     = g++
CFLAGS = -O3 -std=c++11 -isystem ./include
DFLAGS = -std=c++11 -isystem ${GTEST_DIR}/include ${GTEST_DIR}/build/libgtest.a -pthread include/*.cpp
OBJ    = digraph.o propertymanager.o
ALGS   = dfs.o bfs.o

# Build demos
all: $(OBJ) $(ALGS)
	make dirs
	$(CC) demos/demo01.cpp -o build/demos/demo01 $(OBJ) $(CFLAGS)
	$(CC) demos/demo02.cpp -o build/demos/demo02 $(OBJ) $(CFLAGS)
	$(CC) demos/demo03.cpp -o build/demos/demo03 $(OBJ) $(CFLAGS)
	$(CC) demos/demo04.cpp -o build/demos/demo04 $(OBJ) $(CFLAGS)
	$(CC) demos/demo05.cpp -o build/demos/demo05 $(OBJ) $(CFLAGS)
	$(CC) demos/demo06.cpp -o build/demos/demo06 $(OBJ) $(ALGS) $(CFLAGS)
	# Demos saved to: build/demos

# Build unit tests
test:
	make dirs
	$(CC) unittest/unittest.cpp -o build/unittest/unittest.ut $(DFLAGS)
	# Unit tests saved to: build/unittest

# Build coverage tests
coverage:
	make dirs
	$(CC) unittest/unittest.cpp -o build/unittest/unittest.ut $(DFLAGS) --coverage
	mv *.gcno build/unittest
	build/unittest/unittest.ut
	mv *.gcda build/unittest
	lcov -t "unittest" -o build/unittest/unittest.info -c -d build/unittest
	genhtml -o build/unittest/testcoverage/ build/unittest/unittest.info
	rm build/unittest/*.gcda
	rm build/unittest/*.gcno
	rm build/unittest/*.info
	xdg-open build/unittest/testcoverage/index.html &
	# Coverage tests report saved to: build/unittest/testcoverage/index.html

# Set up build directories
dirs:
	if [ ! -d "build" ]; then mkdir build; fi
	if [ ! -d "build/demos" ]; then mkdir build/demos; fi
	if [ ! -d "build/unittest" ]; then mkdir build/unittest; fi

# Clean build files
clean:
	rm -rfv build
	rm *.o

# Compile objects
%.o: ./include/%.cpp
	$(CC) -c -o $@ $< $(CFLAGS)
