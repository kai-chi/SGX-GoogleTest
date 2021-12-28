# SGX-GoogleTest
Writing Intel SGX Unit Tests with GoogleTest

Read how to start writing your own tests in this [blog post](https://kai-chi.github.io/2021/12/28/writing-intel-sgx-unit-tests-with-googletest.html).

## Build
```
mkdir build && cd build
cmake -S .. -B . && cmake --build .
```

## Run tests
```
ctest
```
