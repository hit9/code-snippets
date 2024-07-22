default: build

install:
	conan install . --output-folder=build --build=missing -s compiler.cppstd=20

configure:
	cd build && cmake .. \
        -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_EXPORT_COMPILE_COMMANDS=1

build:
	make -C build

.PHONY: build
