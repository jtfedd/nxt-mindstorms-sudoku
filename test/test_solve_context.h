#ifndef TEST_SOLVE_CONTEXT
#define TEST_SOLVE_CONTEXT

#include "test/testing.h"
#include "test/sudoku_puzzles.h"

#include "src/solve/solve_context.h"

void Test_InitSolveCtx1(test_case &tc) {
  solve_context ctx;
  init_solve_context(ctx, easy);

  assertEqual(tc, 34, ctx.solved_count);

  assertEqual(tc, 9, ctx.board[1][0]);
  assertEqual(tc, 7, ctx.board[5][3]);
  assertEqual(tc, 0, ctx.board[3][1]);
}

void Test_InitSolveCtx2(test_case &tc) {
  solve_context ctx;
  init_solve_context(ctx, easy);
  
  assertEqual(tc, 0x90, ctx.position_possibilities[0][0]); // 7 and 4
}

#endif
