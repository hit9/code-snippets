how to run tests:

1. Install Catch2:

   ```bash
   conan install . --output-folder=build --build=missing
   ```

2. Run CMake:

   ```bash
   cd build && cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=1
   ```

3. Run tests:

   ```bash
   make runtests
   ```
