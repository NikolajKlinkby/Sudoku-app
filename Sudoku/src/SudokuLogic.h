#ifndef SUDOKULOGIC_H
#define SUDOKULOGIC_H
class Sudoku  // The class
{
private:
    /*-- Private attributes --*/
    int rnd_number_list[9]{1,2,3,4,5,6,7,8,9};

    int annotation_solver_sudoku_array[9][9][9]{};
    int solver_sudoku_array[9][9]{};

    int solver_row_array[9];
    int solver_col_array[9];
    int solver_square_array[3][3];

    /*-- private member functions --*/

    void set_solver_col_to_current(int i);
    void set_solver_row_to_current(int i);
    void set_solver_square_to_current(int row,int col);

    bool check_solver_grid();

    //Solver logic
    void set_annotations();
    bool naked_singles();
    bool hidden_singles();


public: // Access specifier for class

    /*-- Public attributes --*/
    int sudoku_array[9][9]{};
    int solved_sudoku_array[9][9]{};

    int row_array[9];
    int col_array[9];
    int square_array[3][3];

    /*-- Constructor --*/
    void Construct_Sudoku();

    /* -- Member Functions --*/
    void initialize_array();

    void set_col_to_current(int i);
    void set_row_to_current(int i);
    void set_square_to_current(int row,int col);

    void set_rnd_number_list();

    bool is_possible(int row, int col, int number);

    bool check_grid();

    bool fill_array();

    bool call_solvers();

    bool solve_grid();

    void print_sudoku();

    void set_sudoku(int max_rm_cells);

};


#endif //SUDOKULOGIC_H