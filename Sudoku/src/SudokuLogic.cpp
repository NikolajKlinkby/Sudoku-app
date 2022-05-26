#include "SudokuLogic.h"

AnnotationTensor::AnnotationTensor(int (&grid)[9][9]) {

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


void Sudoku::initialize_sudoku()
{
    for(int row = 0; row < 9; row++)
    {
        for(int col = 0; col < 9; col++)
        {
            this->sudoku_grid[row][col] = 0;
        }
    }
}

