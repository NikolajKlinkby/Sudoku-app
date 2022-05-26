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



class AnnotationTensor{
private:
    /* --- Attributes --- */
    int annotation_data[9][9];
public:
    AnnotationTensor(int (&grid)[9][9]);
    void set_annotation(int row, int col, int number);
    void remove_annotation(int row, int col, int number);
    int count_annotations(int row, int col);
    void update(int row, int col, int number);
};

#endif //SUDOKULOGIC_H