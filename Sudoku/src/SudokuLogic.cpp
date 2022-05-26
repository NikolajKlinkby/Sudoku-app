#include "SudokuLogic.h"
#include <chrono>
#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <utility>


////////////////// ANNOTATION TENSOR CLASS FUNCTIONS //////////////////


AnnotationTensor::AnnotationTensor() {
    for(auto & row : annotation_data){
        for(int & col : row){
            col = 0;
        }
    }
}

void AnnotationTensor::set_annotation(int row, int col, int number) {
    annotation_data[row][col] |= 1 << number;
}
void AnnotationTensor::remove_annotation(int row, int col, int number) {
    annotation_data[row][col] 
}
int AnnotationTensor::count_annotations(int row, int col) {
    return annotation_data[row][col] >> 9;
}
void AnnotationTensor::update(int row, int col, int number) {
    for(int )
}


/* -- Member Functions --*/
void Sudoku::initialize_sudoku() {
    for(auto & row : sudoku_array) {
        for(int & col : row) {
            col = 0;
        }
    }
}

void Sudoku::set_solved_sudoku()
{
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            solved_sudoku_array[i][j] = sudoku_array[i][j];
        }
    }
}

void Sudoku::set_rnd_number_list()
{
    // setting vector with integers
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    // get a time-based seed
    unsigned seed = std::chrono::system_clock::now()
            .time_since_epoch()
            .count();

    // randomly shuffle vector
    shuffle (v.begin(), v.end(), std::default_random_engine(seed));

    // append values to rnd_number_list
    for(int i = 0; i < 9; i++)
    {
        rnd_number_list[i] = v[i];
    }
}


void Sudoku::print_rnd_number_list()
{
    for(int i = 0; i < 9; i++)
    {
        std::cout << rnd_number_list[i] << " ";
    }
}

void Sudoku::set_position_list()
{
    for(int row = 0; row < 9; row++)
    {
        for(int col = 0; col < 9; col++)
        {
            position_list.push_back(std::make_pair(row,col));
        }
    }
}

void Sudoku::shuffle_position_list()
{
    // get a time-based seed
    unsigned seed = std::chrono::system_clock::now()
            .time_since_epoch()
            .count();

    // randomly shuffle vector
    shuffle (position_list.begin(), position_list.end(), std::default_random_engine(seed));
}

void Sudoku::print_position_list()
{
    for(int i = 0; i < 81; i++)
    {
        std::cout<<"("<<position_list[i].first<<","<<position_list[i].second<<")"<<"\n";
    }
}

bool Sudoku::is_possible(int row, int col, int number)
{
    // Checking column
    for(auto & row_i : sudoku_array)
    {
        if (row_i[col] == number)
        {
            return false;
        }
    }
    // Checking row
    for(int col_i = 0; col_i < 9; col_i++)
    {
        if (sudoku_array[row][col_i] == number)
        {
            return false;
        }
    }
    // Checking Square
    int row_0 = (int)(floor((double)row/3) * 3);
    int col_0 = (int)(floor((double)col/3) * 3);
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
    // If everything is ok
    return true;
}

bool Sudoku::check_grid()
{
    for(auto & row : sudoku_array)
    {
        for(int col : row)
        {
            if (col == 0)
            {
                return false;
            }
        }
    }
    // If no zeros remain
    return true;
}

bool Sudoku::fill_sudoku()
{
    // Re-shuffling rnd number list
    set_rnd_number_list();

    // Main recursion
    int row, col;
    for (int i = 0; i < 81; i++)
    {
        row = (int)floor((double)i/9);
        col = i % 9;
        if (sudoku_array[row][col] == 0)
        {
            for (int number : rnd_number_list)
            {
                if (is_possible(row,col,number))
                {
                    sudoku_array[row][col] = number;
                    if (check_grid())
                    {
                        return true;
                    }
                    else
                    {
                        if (fill_sudoku())
                        {
                            return true;
                        }
                    }
                }
            }
            break;
        }
    }
    sudoku_array[row][col] = 0;
    return false; // HUSK DET HER FUCKING RETURN STATEMENT - ELLER DØ I HELVEDE!!
}

void Sudoku::print_sudoku(int array[9][9])
{
    for(int i = 0; i < 9; i++)
    {
        if(i == 3 || i == 6)
        {
            std::cout << "----------------------------" << "\n";
        }
        for(int j = 0; j < 9; j++)
        {
            if(j == 3 || j == 6)
            {
                std::cout << "| " << array[i][j] << " ";
            }
            else
            {
                std::cout << " " << array[i][j] << " ";
            }
        }
        std::cout << "\n";
    }
}
void Sudoku::print_sudoku()
{
    print_sudoku(sudoku_array);
}

void Sudoku::crappy_set_sudoku()
{
    // Placeholder variable
    int currently_removed;

    // Shuffling positions
    shuffle_position_list();

    // counter variable
    int pos_nr = 0;

    /*--- Main loop ---*/
    while (pos_nr < 81)
    {
        int row = position_list[pos_nr].first;
        int col = position_list[pos_nr].second;
        currently_removed = sudoku_array[row][col];
        sudoku_array[row][col] = 0;

        // Re-shuffling rnd number list
        set_rnd_number_list();

        // Counting number of solutions
        int solution_counter = 0;
        for(int i = 0; i < 9; i++)
        {
            int number = rnd_number_list[i];
            if(is_possible(row,col,number))
            {
                solution_counter++;
            }
        }

        //  multiple solutions -> Undo current removal
        if (solution_counter > 1)
        {
            sudoku_array[row][col] = currently_removed;
            pos_nr++;

        }
            // perfect! still only one solution
        else if (solution_counter == 1)
        {
            pos_nr++;
        }
            // no solutions :((
        else if (solution_counter == 0)
        {
            break;
        }
    }
}

std::pair<int,int> Sudoku::random_walk()
{
    int row = rand() % 9;
    int col = rand() % 9;
    while(sudoku_array[row][col] == 0)
    {
        row = rand() % 9;
        col = rand() % 9;
    }
    return std::pair<int,int>(row, col);
}

bool Sudoku::solvable() {
    if (naked_single()){
        if (check_grid()){
            return true;
        }
        else{
            if (solvable()){
                return true;
            }
        }
    }
    else if (hidden_single()){
        if (solvable()){
            return true;
        }
    }
    return false;
}

void Sudoku::set_sudoku(int remaining_numbers)
{
    int MAX_ITER = 100;
    int nr_of_holes = 81 - remaining_numbers;

    int nr_current_holes = 0;
    int counter = 0;
    std::vector<std::pair<int,int>> zero_positions;
    std::pair<int,int> current_position;
    int number_buff;
    while ((nr_current_holes < nr_of_holes) && (counter < MAX_ITER))
    {
        for(auto (&position): zero_positions)
        {
            sudoku_array[position.first][position.second] = 0;
        }

        current_position = random_walk();
        number_buff      = sudoku_array[current_position.first][current_position.second];
        sudoku_array[current_position.first][current_position.second] = 0;

        annotation_tensor.fill_annotation(sudoku_array);
        if(solvable())
        {
            nr_current_holes++;
            zero_positions.emplace_back(current_position);
        }
        else
        {
            sudoku_array[current_position.first][current_position.second] = number_buff;

            annotation_tensor.fill_annotation(sudoku_array);
        }
        counter++;
        if (counter >= MAX_ITER) std::cout << "MAX ØV BØV NÅET" << std::endl;
    }
    for(auto (&position): zero_positions)
    {
        sudoku_array[position.first][position.second] = 0;
    }
}

////////////////// UTILITY FUNCTIONS //////////////////
bool is_possible(int row, int col, int number, int (&sudoku_grid)[9][9])
{
    // Checking column
    for(auto & row_i : sudoku_grid)
    {
        if (row_i[col] == number)
        {
            return false;
        }
    }
    // Checking row
    for(int col_i = 0; col_i < 9; col_i++)
    {
        if (sudoku_grid[row][col_i] == number)
        {
            return false;
        }
    }
    // Checking Square
    int row_0 = (int)(floor((double)row/3) * 3);
    int col_0 = (int)(floor((double)col/3) * 3);
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(sudoku_grid[row_0 + i][col_0 + j] == number)
            {
                return false;
            }
        }
    }
    // If everything is ok
    return true;
}