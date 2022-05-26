#ifndef SODUKUWIDGET_H
#define SODUKUWIDGET_H


class SudkoWidget {

public:
    bool SudokuCell();


};


#endif //SODUKUWIDGET_H


typedef int ImGuiSudokuCellFlags;

enum ImGuiSudokuCellFlags_{
    ImGuiSudokuCellFlags_None                = 0,
    ImGuiSudokuCellFlags_ReadOnly            = 1 << 0,
    ImGuiSudokuCellFlags_CallbackResize      = 1 << 1,
    ImGuiSudokuCellFlags_MergedItem           = 1 << 2,
    ImGuiSudokuCellFlags_CallbackHistory      = 1 << 3,
    ImGuiSudokuCellFlags_CallbackEdit         = 1 << 4,
    ImGuiSudokuCellFlags_CallbackAlways       = 1 << 5
};