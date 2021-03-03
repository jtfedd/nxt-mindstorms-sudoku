#ifndef TESTING_H
#define TESTING_H

// Unit test runner utils

string BoolToStr(bool value) {
  string result = "false";
  if (value) {
    result = "true";
  }
  return result;
}

struct readable_description {
  string expected;
  string actual;
};

struct test_case {
  string name;
  readable_description description;
  bool passing;
};

void assign_result(test_case &tc, string e, string a, bool result) {
  if (!tc.passing) {
    return;
  }

  tc.passing = result;
  tc.description.expected = e;
  tc.description.actual = a;
}

void assertTrue(test_case &tc, bool result) {
  assign_result(tc, "true", BoolToStr(result), result);
}

void assertFalse(test_case &tc, bool result) {
  assign_result(tc, "false", BoolToStr(result), !result);
}

void assertEqual(test_case &tc, int expected, int actual) {
  assign_result(tc, NumToStr(expected), NumToStr(actual), expected == actual);
}

void show_current_test(int current, int total) {
  ClearScreen();
  TextOut(0, LCD_LINE1, "Running test");
  NumOut(0, LCD_LINE2, current + 1);
  TextOut(15, LCD_LINE2, "of");
  NumOut(30, LCD_LINE2, total);
}

void draw_summary(test_case &tests[], int test_count) {
  ClearScreen();
  TextOut(0, LCD_LINE1, "Tests Complete");
  TextOut(0, LCD_LINE2, "Passed:");
  TextOut(0, LCD_LINE3, "Failed:");
  
  int passed = 0;
  int failed = 0;
  
  for (int i = 0; i < test_count; i++) {
    if (tests[i].passing) {
      passed++;
    } else {
      failed++;
    }
  }

  NumOut(40, LCD_LINE2, passed);
  NumOut(40, LCD_LINE3, failed);
}

void draw_failed_test(test_case tc) {
  ClearScreen();
  TextOut(0, LCD_LINE1, tc.name);
  TextOut(0, LCD_LINE2, "Failed");
  TextOut(0, LCD_LINE3, "Expected:");
  TextOut(10, LCD_LINE4, tc.description.expected);
  TextOut(0, LCD_LINE5, "Actual:");
  TextOut(10, LCD_LINE6, tc.description.actual);
}

void show_results(test_case &tests[], int test_count) {
  draw_summary(tests, test_count);
  
  int current_test_index = -2;
  
  while(true) {
    while(!ButtonPressed(BTNLEFT, false) && !ButtonPressed(BTNRIGHT, false)) {
      Wait(100);
    }
    bool found_failed_test = false;
    if (ButtonPressed(BTNLEFT, false)) {
      int search_start = current_test_index;
      if (search_start == -2) {
        search_start = test_count;
      }
      for (int i = search_start - 1; i >= 0; i--) {
        if (!tests[i].passing) {
          current_test_index = i;
          found_failed_test = true;
          draw_failed_test(tests[i]);
          break;
        }
      }
    }
    if (ButtonPressed(BTNRIGHT, false)) {
      int search_start = current_test_index;
      if (search_start == -2) {
        search_start = -1;
      }
      for (int i = search_start + 1; i < test_count; i++) {
        if (!tests[i].passing) {
          current_test_index = i;
          found_failed_test = true;
          draw_failed_test(tests[i]);
          break;
        }
      }
    }
    if (!found_failed_test) {
      draw_summary(tests, test_count);
      current_test_index = -2;
    }
    while(ButtonPressed(BTNLEFT, false) || ButtonPressed(BTNRIGHT, false)) {
      Wait(100);
    }
  }
}

#endif
