#ifndef SUDOKULOGIC_H
#define SUDOKULOGIC_H
#include<stdlib.h>
#include<vector>
#include <chrono>
#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <algorithm>
#include <utility>
class AnnotationTensor{
private:

    /* --- Functions --- */

    /* --- Attributes --- */
    int annotation_data[9][9]{};
public:
    AnnotationTensor();
    AnnotationTensor(int (&grid)[9][9]);
    void fill_annotation(int (&grid)[9][9]);
    void set_annotation(int row, int col, int number);
    bool remove_annotation(int row, int col, int number);
    void clear_cell(int row, int col);
    int get_annotation_count(int row, int col);
    void update(int row, int col, int number);
    bool has_annotation(int row, int col, int number);
    std::vector<int> get_annotations(int row, int col);
    int get_data(int row, int col);
};

class Sudoku {
private:
    /* --- Functions --- */
    bool naked_single();
    bool hidden_single();
    bool naked_cells(int start, int end);
    bool hidden_cells(int start, int end);
    /* --- Attributes --- */

public:

    /* --- Default constructor --- */
    Sudoku(){
        // Setting randomly shuffled list of ints (1-9).
        set_rnd_number_list();
        // Initializing sudoku array (filling with zeroes).
        initialize_sudoku();
        // Setting filled sudoku array.
        fill_sudoku();
        // Copying fully solved sudoku sudoku_array -> solved_sudoku_array.
        set_solved_sudoku();
        // Setting vector list of pairs of ints representing positions in sudoku array.
        set_position_list();
    }

    /* --- Paramtrized constructor --- */

    /* --- Functions ---*/
    void initialize_sudoku();
    void set_solved_sudoku();
    void set_rnd_number_list();
    void set_position_list();
    void shuffle_position_list();
    bool is_possible(int row, int col, int number);
    bool check_grid();
    bool fill_sudoku();
    void print_sudoku();
    void print_sudoku(int array[9][9]);
    void print_rnd_number_list();
    void print_position_list();
    int set_sudoku(int remaining_numbers);
    bool solvable();



    /* --- Attributes ---*/
    int sudoku_array[9][9];
    int solved_sudoku_array[9][9];
    int rnd_number_list[9];
    std::vector <std::pair<int,int>> position_list;
    AnnotationTensor annotation_tensor;
};

bool is_possible(int row, int col, int number, int (&sudoku_grid)[9][9]);
void erase_value(std::vector<int> & vec,int val);
void all_unique_permutations(std::vector<int> & possible, std::vector<int> & combination, int n, int current_pos);

#endif //SUDOKULOGIC_H