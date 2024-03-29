# LEGO Mindstorms NXT Sudoku Solver

This is a project to build a LEGO Mindstorms NXT robot that is capable of solving sudoku puzzles.

Inspired by [this video](https://www.youtube.com/watch?v=Mp8Y2yjV4fU).

## Getting Started

This program is written in NXC using the [Bricx Command Center](http://bricxcc.sourceforge.net/).

There are some python scripts in the `tools` directory to aid in development.

```bash
# Removes generated files from the nxc compile process
python ./tools/clean.py
# Regenerates the unit test runner program from tests found in the `test` folder
python ./tools/gen_test_runner.py
```

Current solve benchmarks:

| Puzzle | Solved | Time (ms) | Iterations | Guesses |
| ------------ | ------------ | ------------ | ------------ | ------------ |
| Easy | True | 1344 | 7 | 0 |
| Medium | True | 2307 | 10 | 0 |
| Hard | True | 4150 | 17 | 4 |
| Expert | True | 7981 | 23 | 7 |
| Evil | True | 5026 | 15 | 8 |
