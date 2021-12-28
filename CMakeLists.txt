cmake_minimum_required(VERSION 2.8)
project(sgx_gtest)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
find_package(SGX REQUIRED)


include_directories(Include Enclave App)
set(EDL_SEARCH_PATHS Enclave)

set(E_SRCS Enclave/Enclave.cpp)
set(T_SRCS Enclave/TrustedLibrary/Libc.cpp Enclave/TrustedLibrary/Libcxx.cpp Enclave/TrustedLibrary/Thread.cpp
        Enclave/Edger8rSyntax/Arrays.cpp Enclave/Edger8rSyntax/Functions.cpp Enclave/Edger8rSyntax/Pointers.cpp Enclave/Edger8rSyntax/Types.cpp)
set(LDS Enclave/Enclave.lds)

add_trusted_library(trusted_lib SRCS ${T_SRCS} EDL Enclave/Enclave.edl EDL_SEARCH_PATHS ${EDL_SEARCH_PATHS})
add_enclave_library(enclave SRCS ${E_SRCS} TRUSTED_LIBS trusted_lib EDL Enclave/Enclave.edl EDL_SEARCH_PATHS ${EDL_SEARCH_PATHS} LDSCRIPT ${LDS})
enclave_sign(enclave KEY Enclave/Enclave_private_test.pem CONFIG Enclave/Enclave.config.xml)

set(SRCS App/App.cpp App/TrustedLibrary/Libc.cpp App/TrustedLibrary/Libcxx.cpp App/TrustedLibrary/Thread.cpp
        App/Edger8rSyntax/Arrays.cpp App/Edger8rSyntax/Functions.cpp App/Edger8rSyntax/Pointers.cpp App/Edger8rSyntax/Types.cpp)
add_untrusted_executable(app SRCS ${SRCS} EDL Enclave/Enclave.edl EDL_SEARCH_PATHS ${EDL_SEARCH_PATHS})
add_dependencies(app enclave-sign)

# GTEST

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_untrusted_executable(arrays_test
                         SRCS App/Edger8rSyntax/Functions.cpp App/Edger8rSyntax/Pointers.cpp test/arrays_test.cc
                         EDL Enclave/Enclave.edl
                         EDL_SEARCH_PATHS ${EDL_SEARCH_PATHS})


target_link_libraries(
        arrays_test
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(arrays_test)
