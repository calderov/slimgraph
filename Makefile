all:
	# COMPILING DEMOS TO ./build/demos/
	if [ ! -d "build" ]; then mkdir build; fi
	if [ ! -d "build/demos" ]; then mkdir build/demos; fi
	g++ -std=c++11 -isystem ./include demos/demo01.cpp include/graph.cpp include/propertymanager.cpp -O3 -o build/demos/demo01
	g++ -std=c++11 -isystem ./include demos/demo02.cpp include/graph.cpp include/propertymanager.cpp -O3 -o build/demos/demo02
	g++ -std=c++11 -isystem ./include demos/demo03.cpp include/graph.cpp include/propertymanager.cpp -O3 -o build/demos/demo03
	g++ -std=c++11 -isystem ./include demos/demo04.cpp include/graph.cpp include/propertymanager.cpp -O3 -o build/demos/demo04
	g++ -std=c++11 -isystem ./include demos/demo05.cpp include/graph.cpp include/propertymanager.cpp -O3 -o build/demos/demo05

debug:
	# COMPILING DEBUG DEMOS TO ./build/debug/
	if [ ! -d "build" ]; then mkdir build; fi
	if [ ! -d "build/debug" ]; then mkdir build/debug; fi
	g++ -g -std=c++11 -isystem ./include demos/demo01.cpp include/graph.cpp include/propertymanager.cpp -o build/debug/demo01
	g++ -g -std=c++11 -isystem ./include demos/demo02.cpp include/graph.cpp include/propertymanager.cpp -o build/debug/demo02
	g++ -g -std=c++11 -isystem ./include demos/demo03.cpp include/graph.cpp include/propertymanager.cpp -o build/debug/demo03
	g++ -g -std=c++11 -isystem ./include demos/demo04.cpp include/graph.cpp include/propertymanager.cpp -o build/debug/demo04
test:
	# COMPILING UNIT TESTS TO ./build/unittests/
	if [ ! -d "build" ]; then mkdir build; fi
	if [ ! -d "build/unittest" ]; then mkdir build/unittest; fi
	g++ -std=c++11 -isystem ${GTEST_DIR}/include -pthread unittest/test01.cpp include/graph.cpp include/propertymanager.cpp ${GTEST_DIR}/build/libgtest.a -o build/unittest/test01.ut
	build/unittest/test01.ut

coverage:
	# COMPILING AND RUNNING COVERAGE TESTS
	if [ ! -d "build" ]; then mkdir build; fi
	if [ ! -d "build/unittest" ]; then mkdir build/unittest; fi
	g++ -std=c++11 -isystem ${GTEST_DIR}/include -pthread unittest/test01.cpp include/graph.cpp include/propertymanager.cpp ${GTEST_DIR}/build/libgtest.a -o build/unittest/test01.ut --coverage
	mv *.gcno build/unittest
	build/unittest/test01.ut
	mv *.gcda build/unittest
	lcov -t "test01" -o build/unittest/test01.info -c -d build/unittest
	genhtml -o build/unittest/test01COV build/unittest/test01.info
	# COVERAGE TEST REPORT SAVED TO build/unittest/test01COV/index.html

clean:
	# DELETING BUILDS FOR DEMOS (RELEASE & DEBUG), UNIT TESTS AND COVERAGE TESTS
	rm -rfv build/
