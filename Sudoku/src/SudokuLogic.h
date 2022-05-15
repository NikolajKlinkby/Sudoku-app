#ifndef SUDOKULOGIC_H
#define SUDOKULOGIC_H
class Sudoku  // The class
{
private:

    /*-- Private attributes --*/
    int rnd_number_list[9]{};

public: // Access specifier for class

    /*-- Public attributes --*/
    int sudoku_array[9][9]{};

    /*-- Constructor --*/
    void Construct_Sudoku();

    /* -- Member Functions --*/
    void initialize_array();

    void set_rnd_number_list();

    bool is_possible(int row, int col, int number);

    bool check_grid();

    bool fill_array();

    void print_sudoku();

};
#endif //SUDOKULOGIC_H