#include <gtest/gtest.h>
#include "Enclave_u.h"
#include "sgx_urts.h"
#include "sgx_error.h"       /* sgx_status_t */
#include "sgx_eid.h"     /* sgx_enclave_id_t */
# define ENCLAVE_FILENAME "enclave.signed.so"

class ArraysTest : public ::testing::Test {
protected:
    void SetUp() override {
        sgx_status_t ret = SGX_ERROR_UNEXPECTED;
        ret = sgx_create_enclave(ENCLAVE_FILENAME, SGX_DEBUG_FLAG,NULL,NULL,&test_eid,NULL);
        if (ret != SGX_SUCCESS) {
            // print error
        }
    }

    void TearDown() override {
        sgx_destroy_enclave(test_eid);
    }

    sgx_enclave_id_t test_eid = 0;
};

TEST_F(ArraysTest, ArrayUserCheck) {
    int arr[4] = {0, 1, 2, 3};
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;
    ret = ecall_array_user_check(test_eid, arr);
    EXPECT_EQ(ret, SGX_SUCCESS);
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(arr[i], (3 - i));
    }
}

TEST_F(ArraysTest, ArrayIn) {
    int arr[4] = {0, 1, 2, 3};
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;
    ret = ecall_array_in(test_eid, arr);
    EXPECT_EQ(ret, SGX_SUCCESS);
    for (int i = 0; i < 4; i++) {
       EXPECT_EQ(arr[i], i);
    }
}

TEST_F(ArraysTest, ArrayOut) {
    int arr[4] = {0, 1, 2, 3};
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;
    ret = ecall_array_in_out(test_eid, arr);
    EXPECT_EQ(ret, SGX_SUCCESS);
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(arr[i], (3 - i));
    }
}

TEST_F(ArraysTest, Isary) {
    array_t arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;
    ret = ecall_array_isary(test_eid, arr);
    EXPECT_EQ(ret, SGX_SUCCESS);
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(arr[i], (9 - i));
    }
}