defalut: build

install:
	conan install . --output-folder=build --build=missing -s compiler.cppstd=20 -s build_type=Release

cmake-build:
	cd build && cmake .. \
		-DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake \
		-DCMAKE_BUILD_TYPE=Release \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
		-DSEGBITSET_TEST=1 \
		-DCMAKE_CXX_STANDARD=20

build-test:
	cd build && make segbitset_tests

run-tests: build-test
	ctest --test-dir ./build --output-on-failure

build-benchmark:
	cd build && make segbitset_benchmark

run-benchmark: build-benchmark
	./build/segbitset_benchmark

clean:
	make -C build clean

lint:
	cppcheck *.h --enable=warning,style,performance,portability --inline-suppr --language=c++

.PHONY: build-test
