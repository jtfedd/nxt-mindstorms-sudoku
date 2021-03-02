#ifndef TEST_TESTS
#define TEST_TESTS

#include "test/testing.h"

test_case Test_Test1(test_case &tc) {
  assertTrue(tc, true);
  assertTrue(tc, true);
}

test_case Test_Test2(test_case &tc) {
  assertFalse(tc, false);
  assertTrue(tc, false);
}

test_case Test_Test3(test_case &tc) {
  assertTrue(tc, true);
  assertFalse(tc, true);
}

test_case Test_Test4(test_case &tc) {
  assertFalse(tc, false);
  assertFalse(tc, false);
}

test_case Test_Test5(test_case &tc) {
  assertEqual(tc, -1, -1);
  assertEqual(tc, 15, 15);
  assertEqual(tc, 1551, 1551);
  assertEqual(tc, 1351, 1351);
}

test_case Test_Test6(test_case &tc) {
  assertEqual(tc, 1, 1);
  assertTrue(tc, true);
  assertFalse(tc, false);
  assertEqual(tc, 13531, 135);
  assertTrue(tc, true);
  assertFalse(tc, true);
  assertEqual(tc, 1, -1);
}

#endif
