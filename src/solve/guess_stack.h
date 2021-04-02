#ifndef GUESS_STACK_H
#define GUESS_STACK_H

#include "src/solve/solve_context.h"

#define MAX_GUESS_DEPTH 2

struct guess_stack {
    int solve_count_list[];
    int guess_list[];
    int row_list[];
    int col_list[];
    
    int board_list[];
    int possibilities_list[];

    int length;
};

void init_guess_stack(guess_stack &stack) {
    stack.length = 0;

    ArrayInit(stack.solve_count_list, 0, MAX_GUESS_DEPTH);
    ArrayInit(stack.guess_list, 0, MAX_GUESS_DEPTH);
    ArrayInit(stack.row_list, 0, MAX_GUESS_DEPTH);
    ArrayInit(stack.col_list, 0, MAX_GUESS_DEPTH);
    
    ArrayInit(stack.board_list, 0, 9*9*MAX_GUESS_DEPTH);
    ArrayInit(stack.possibilities_list, 0, 9*9*MAX_GUESS_DEPTH);
}

bool push(guess_stack &stack, solve_context &ctx, int row, int col, int guess) {
    if (stack.length == MAX_GUESS_DEPTH) {
        return false;
    }

    stack.solve_count_list[stack.length] = ctx.solved_count;
    stack.guess_list[stack.length] = guess;
    stack.row_list[stack.length] = row;
    stack.col_list[stack.length] = col;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            stack.board_list[(stack.length * MAX_GUESS_DEPTH) + (i * 9) + j] = ctx.board[i][j];
            stack.possibilities_list[(stack.length * MAX_GUESS_DEPTH) + (i * 9) + j] = ctx.position_possibilities[i][j];
        }
    }

    stack.length = stack.length + 1;

    return true;
}

void pop(guess_stack &stack, solve_context &ctx, int &row, int &col, int &guess) {
    stack.length = stack.length - 1;

    guess = stack.guess_list[stack.length];
    row = stack.row_list[stack.length];
    col = stack.col_list[stack.length];
    ctx.solved_count = stack.solve_count_list[stack.length];

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            ctx.board[i][j] = stack.board_list[(stack.length * MAX_GUESS_DEPTH) + (i * 9) + j];
            ctx.position_possibilities[i][j] = stack.possibilities_list[(stack.length * MAX_GUESS_DEPTH) + (i * 9) + j];
        }
    }
}

#endif
