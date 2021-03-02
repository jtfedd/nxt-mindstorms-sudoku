#ifndef TEST_TESTS
#define TEST_TESTS

#include "test/testing.h"

test_case Test_Test1(test_case &tc) {
  assertTrue(tc, true);
}

test_case Test_Test2(test_case &tc) {
  assertTrue(tc, false);
}

test_case Test_Test3(test_case &tc) {
  assertFalse(tc, true);
}

test_case Test_Test4(test_case &tc) {
  assertFalse(tc, false);
}

test_case Test_Test5(test_case &tc) {
  assertEqual(tc, 1351, 1351);
}

test_case Test_Test6(test_case &tc) {
  assertEqual(tc, 13531, 135);
}

#endif
