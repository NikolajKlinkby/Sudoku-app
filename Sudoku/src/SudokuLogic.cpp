#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>
#include <iterator>
#include "SudokuLogic.h"


    /*-- Private member functions --*/

void Sudoku::set_solver_col_to_current(int i){
    for (int j = 0; j < 9; j++){
        solver_col_array[j] = solver_sudoku_array[j][i];
    }
}
void Sudoku::set_solver_row_to_current(int i){
    for (int j = 0; j < 9; j++){
        solver_row_array[j] = solver_sudoku_array[i][j];
    }
}
void Sudoku::set_solver_square_to_current(int row,int col){
    int row_0 = (int)floor((double)row/3) * 3;
    int col_0 = (int)floor((double)col/3) * 3;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            solver_square_array[i][j] = solver_sudoku_array[row_0 + i][col_0 + j];
        }
    }
}


bool Sudoku::check_solver_grid()
{
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            if (solver_sudoku_array[i][j] == 0)
            {
                return false;
            }
        }
    }
    return true;
}


void Sudoku::set_annotations(){
    //Looping over all cells
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            //If a cell is not filled, fill it's annotation
            if (solver_sudoku_array[i][j] == 0){

                //Check the row, column and square
                set_solver_col_to_current(j);
                set_solver_row_to_current(i);
                set_solver_square_to_current(i, j);

                //For every digit in the sudoku check if we could possibly set the digit
                for (int k = 1; k < 10; k++) {
                    //Check the column
                    if (std::find(std::begin(solver_col_array), std::end(solver_col_array), k) != std::end(solver_col_array)) {
                        annotation_solver_sudoku_array[i][j][k] = 0;
                    }//Check the row
                    else if (std::find(std::begin(solver_row_array), std::end(solver_row_array), k) != std::end(solver_row_array)) {
                        annotation_solver_sudoku_array[i][j][k] = 0;
                    }//Check the square
                    else if (std::find(std::begin(*solver_square_array), std::end(*solver_square_array), k) != std::end(*solver_square_array)) {
                        annotation_solver_sudoku_array[i][j][k] = 0;
                    }//If it is possible to place, then annotate the digit.
                    else {
                        annotation_solver_sudoku_array[i][j][k] = k;
                    }
                }

            }
            //If cell is filled then annotate 0
            else {
                for (int k = 1; k < 10; k++)
                    annotation_solver_sudoku_array[i][j][k] = 0;
            }
        }
    }
}

bool Sudoku::naked_singles() {
    /*-- Checks for naked singles --*/
    int possib;
    int insert_val;
    bool succes = false;

    //Loop over all cells
    //TODO Make this more efficient!
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {

            possib = 0; //Number of possibilities

            //Checking which digits are annotated in cell
            for (int k = 1; k < 10; k++) {
                if (annotation_solver_sudoku_array[i][j][k] != 0) {
                    possib++;
                    insert_val = k;
                }
            }
            //If we only have one possibility then set the digit and return that we have advanced the solve.
            if (possib == 1){
                solver_sudoku_array[i][j] = insert_val;
                succes = true;
            }
        }
    }
    return succes;
}

bool Sudoku::hidden_singles(){
    /*-- Checks for hidden singles --*/
    bool succes = false;

    int insert_index;
    int insert_index_sqr;
    int possib;

    for (int k = 0; k < 9; k++) {

        // Checking rows for hidden k's
        for (int i = 0; i < 9; ++i) {
            possib = 0;
            //On row i, checking all j cells anotation if digit k is annotated
            for (int j = 0; j < 9; ++j) {
                if (annotation_solver_sudoku_array[i][j][k] == k) {
                    possib++;
                    insert_index = j;
                }

            }
            //If only one is possible set the digit and set succes to true
            if (possib == 1) {
                solver_sudoku_array[i][insert_index] = k;
                succes = true;
            }
        }

        // Checking cols for hidden k's
        for (int j = 0; j < 9; ++j) {
            possib = 0;
            //On col j, checking all i cells anotation if digit k is annotated
            for (int i = 0; i < 9; ++i) {
                if (annotation_solver_sudoku_array[i][j][k] == k) {
                    possib++;
                    insert_index = i;
                }

            }
            //If only one is possible set the digit and set succes to true
            if (possib == 1) {
                solver_sudoku_array[insert_index][j] = k;
                succes = true;
            }
        }

        // Checking squares for hidden k's
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                possib = 0;
                //In square row i and square col j search rows l and cols m for singular annotated k
                for (int l = 0; l < 3; ++l) {
                    for (int m = 0; m < 3; ++m) {
                        if (annotation_solver_sudoku_array[i*3+l][j*3+m][k] == k) {
                            possib++;
                            insert_index = i*3+l;
                            insert_index_sqr = j*3+m;
                        }
                    }
                }
                //If only one is possible set the digit and set succes to true
                if (possib == 1) {
                    solver_sudoku_array[insert_index][insert_index_sqr] = k;
                    succes = true;
                }
            }
        }

    }
    return succes;
}


    /* -- Member Functions --*/
void Sudoku::initialize_array()
{
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            sudoku_array[i][j] = 0;
        }
    }
}

void Sudoku::set_rnd_number_list()
{
    std::random_device rd;
    std::mt19937 seed(rd());

    std::shuffle(rnd_number_list,rnd_number_list+9,seed);
}

bool Sudoku::is_possible(int row, int col, int number)
{
    // Checking column
    for(int i = 0; i < 9; i++)
    {
        if (sudoku_array[i][col] == number)
        {
            return false;
        }
    }
    // Checking row
    for(int i = 0; i < 9; i++)
    {
        if (sudoku_array[row][i] == number)
        {
            return false;
        }
    }
    // Checking Square
    int row_0 = (int)floor((double)row/3) * 3;
    int col_0 = (int)floor((double)col/3) * 3;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(sudoku_array[row_0 + i][col_0 + j] == number)
            {
                return false;
            }
        }
    }
    return true;
}

bool Sudoku::check_grid()
{
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            if (sudoku_array[i][j] == 0)
            {
                return false;
            }
        }
    }
    return true;
}

bool Sudoku::fill_array() {
    int row;
    int col;
    Sudoku::set_rnd_number_list();
    for (int i= 0; i < 81; i++) {
        row = (int)floor((double)i/9);
        col = i % 9;
        if (sudoku_array[row][col] == 0){
            for (int j = 0; j < 9; j++) {
                if (is_possible(row, col, rnd_number_list[j])) {
                    sudoku_array[row][col] = rnd_number_list[j];
                    solved_sudoku_array[row][col] = rnd_number_list[j];
                    if (check_grid()) {
                        return true;
                    } else {
                        if (fill_array()) {
                            return true;
                        }
                    }
                }
                sudoku_array[row][col] = rnd_number_list[j];
                solved_sudoku_array[row][col] = rnd_number_list[j];
            }
            break;
        }

    }
    return false;
}

void Sudoku::print_sudoku()
{

    std::cout << " \n     ##### PRINTING SUDOKU ##### \n";
    for(int i = 0; i < 9; i++)
    {
        std::cout << "--------------------------------------" << "\n";
        for(int j = 0; j < 9; j++)
        {
            std::cout << "|" << " " << sudoku_array[i][j] << " ";
        }
        std::cout << "|\n";
    }
    std::cout << "--------------------------------------" << "\n \n";
}

void Sudoku::set_col_to_current(int i){
    for (int j = 0; j < 9; j++){
        col_array[j] = sudoku_array[j][i];
    }
}

void Sudoku::set_row_to_current(int i){
    for (int j = 0; j < 9; j++){
        row_array[j] = sudoku_array[i][j];
    }
}

void Sudoku::set_square_to_current(int row,int col){
    int row_0 = (int)floor((double)row/3) * 3;
    int col_0 = (int)floor((double)col/3) * 3;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            square_array[i][j] = sudoku_array[row_0 + i][col_0 + j];
        }
    }
}

bool Sudoku::call_solvers(){
    Sudoku::set_annotations();
    if (Sudoku::naked_singles()) {
        if (Sudoku::check_solver_grid()) {
            return true;
        }
        else{
            if (Sudoku::call_solvers()){
                return true;
            }
        }
    }
    else if (Sudoku::hidden_singles()){
        if (Sudoku::check_solver_grid()) {
            return true;
        }
        else{
            if (Sudoku::call_solvers()){
                return true;
            }
        }
    }
    else{
        return false;
    }
}

bool Sudoku::solve_grid() {

    //First copy the current grid to the solver grid
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            solver_sudoku_array[i][j] = sudoku_array[i][j];
        }
    }

    //Call solvers until it fails or solves
    return call_solvers();
}

//TODO create flags to enable disable different logic solve methods
void Sudoku::set_sudoku(int max_rm_cells) {
    //Removed value
    int rm_val;
    //Number of removed cells
    int rm_cells = 0;

    int row;
    int col;

    //Setting random number generation
    std::random_device rd;
    std::mt19937 seed(rd());
    std::uniform_int_distribution<int> gen(0, 80);

    int rnd;

    //Something recursive here that revisits all none 0 cells randomly.
    while (rm_cells <= max_rm_cells){
        //initialise the random number
        rnd = gen(seed);
        row = (int) floor((double)rnd/9);
        col = rnd%9;


        //Walk around the grid randomly untill hittimg a none zero cell
        while (sudoku_array[row][col]==0){
            rnd = gen(seed);
            row = (int) floor((double)rnd/9);
            col = rnd%9;
        }

        //Now remove the cell and check if the sudoku is solvable.
        rm_val = sudoku_array[row][col]; //Storing removed value
        sudoku_array[row][col] = 0;
        if (solve_grid()){
            rm_cells += 1;
        }
        else{
            sudoku_array[row][col] = rm_val;
        }

    }
}


    /* --Constructor --*/

void Sudoku::Construct_Sudoku() {
    Sudoku::initialize_array();
    Sudoku::fill_array();
    Sudoku::set_sudoku(50);
}


