#include "sudoku.h"
#include "sudokufile.h"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>

using namespace sudoku;

SudokuLibrary::SudokuLibrary() {
    this->files.clear();
}

void SudokuLibrary::load_library_file(std::string filename) {
    std::ifstream file(filename);
    std::string line;
    std::cout << "Loading library file: " << filename << std::endl;
    if (file.is_open()) {
    while (std::getline(file, line)) {
        this->files.push_back(line);
    }
    file.close();
    } else {
        std::cout << "Error: Could not open file " << filename << std::endl;
    }
}

SudokuFile SudokuLibrary::getsudokufile(int index) {
    SudokuFile sudokufile(this->files[index]);
    return sudokufile;
}

SudokuFile::SudokuFile(const std::string filestring)
{
    for (int x=0; x<9; x++) {
        for (int y=0; y<9; y++) {
            this->board.board[x][y] = filestring.at(y*9+x) - 48;
            this->board.selected[x][y] = false;
            if (this->board.board[x][y] != 0) {
                this->board.started[x][y] = true;
            } else {
                this->board.started[x][y] = false;
            }
        }
    }
    this->board.legal_check = false;
}

SudokuFile::SudokuFile()
{
    for (int x=0; x<9; x++) {
        for (int y=0; y<9; y++) {
            this->board.board[x][y] = 0;
            this->board.selected[x][y] = false;
            this->board.started[x][y] = false;
        }
    }
    this->board.legal_check = false;
}