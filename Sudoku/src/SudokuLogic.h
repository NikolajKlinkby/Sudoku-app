#ifndef SUDOKULOGIC_H
#define SUDOKULOGIC_H
#include<stdlib.h>
#include<vector>

class Sudoku {
private:
    /* --- Functions --- */
    void initialize_sudoku();
    /* --- Attributes --- */
    int sudoku_grid[9][9];
public:
    /* --- Default constructor --- */
    Sudoku(){}
    /* --- Paramtrized constructor --- */
    Sudoku(int a , int b) {
        // a, b not important
        this->a = a;
        this->b = b;
        // Initializing sudoku with zeros
        initialize_sudoku();
    }
    /* --- Functions ---*/
    /* --- Attributes ---*/
    int a;
    int b;
};


bool is_possible(int row, int col, int number, int (&sudoku_grid)[9][9]);

#endif //SUDOKULOGIC_H