#pragma once

#ifndef CRYPTIKK_SUDOKUFILE_H
#define CRYPTIKK_SUDOKUFILE_H

#include <vector>
#include "sudoku.h"

namespace sudoku {
    class SudokuFile {
        public:
            SudokuFile(std::string);
            SudokuFile();

            sudoku::SudokuBoard board;
    };

    class SudokuLibrary {
        public:
            SudokuLibrary();

            void load_library_file(std::string);
            sudoku::SudokuFile getsudokufile(int);

            std::vector<std::string> files;
    };

}

#endif