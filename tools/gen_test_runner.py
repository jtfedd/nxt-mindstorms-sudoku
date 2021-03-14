import os

test_files = []
for filename in os.listdir('./test'):
    if (filename.startswith('test_') and filename.endswith('.h')):
        print("Found test file " + filename)
        test_files.append('test/' + filename)

print("Extracting test cases...")

test_cases = []
for filename in test_files:
    f = open(filename, "r")
    lines = f.readlines()

    for l in lines:
        if l.startswith("void Test_"):
            test_function_name = l.split(" ")[1].split("(")[0]
            test_name = test_function_name[5:]
            print(test_name)
            test_cases.append(test_name)
    
    f.close()

print("Writing test runner...")

output_lines = []

output_lines.append('// Include the test library')
output_lines.append('#include "test/testing.h"')
output_lines.append('')
output_lines.append('// Include the test files')

for filename in test_files:
    output_lines.append('#include "' + filename + '"')

output_lines.append('')
output_lines.append('#define NUM_TESTS ' + str(len(test_cases)))
output_lines.append('')

output_lines.append('task main() {')
output_lines.append('  test_case tests[NUM_TESTS];')
output_lines.append('  test_case current_test;')
output_lines.append('  for (int i = 0; i < NUM_TESTS; i++) {')
output_lines.append('    tests[i].passing = true;')
output_lines.append('  }')
output_lines.append('')

for i, test_case in enumerate(test_cases):
    output_lines.append('  show_current_test(' + str(i) + ', NUM_TESTS);')
    output_lines.append('  current_test = tests[' + str(i) + '];')
    output_lines.append('  current_test.name = "'+ test_case + '";')
    output_lines.append('  Test_'+ test_case + '(current_test);')
    output_lines.append('  tests[' + str(i) + '] = current_test;')
    output_lines.append('')

output_lines.append('  show_results(tests, NUM_TESTS);')
output_lines.append('}')

f = open('./test_runner.nxc', 'w')
f.write('\n'.join(output_lines))
f.close()

print("Complete!")
