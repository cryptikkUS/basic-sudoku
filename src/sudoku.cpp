#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "sudoku.h"

using namespace sudoku;

SudokuBoard::SudokuBoard() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            this->board[i][j] = 0;
            this->selected[i][j] = false;
            this->legal_check = false;
            this->started[i][j] = false;
            this->legal_squares[i][j] = true;
            this->highlights[i][j] = 0;
            for (int k=0; k < 9; k++) {
                this->pencil_marks[i][j][k] = false;
            }
        }
    }

    this->won = false;

    this->default_box_color = sf::Color::White;
    this->win_box_color = sf::Color::Green;
    this->selected_box_color = sf::Color::Yellow;
    this->error_box_color = sf::Color::Red;
    this->default_text_color = sf::Color::Black;
    this->selected_text_color = sf::Color::Black;
    this->error_text_color = sf::Color::Black;
    this->started_text_color = sf::Color(150, 150, 150);
    this->started_selected_text_color = sf::Color(150, 150, 150);
    this->started_error_text_color = sf::Color(150, 150, 150);
    this->pencil_color = sf::Color(150, 150, 150);
    this->selected_highlighted_box_color = sf::Color(175, 175, 0);
    this->selected_error_box_color = sf::Color(255, 100, 100);

    this->highlight_colors.clear();
    this->highlight_colors.push_back(sf::Color(100, 255, 100)); // Light green
    this->highlight_colors.push_back(sf::Color(255, 165, 0)); // Orange
    this->highlight_colors.push_back(sf::Color::Magenta);
    this->highlight_colors.push_back(sf::Color::Cyan);
}

SudokuBoard::SudokuBoard(int board[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            this->board[i][j] = board[i][j];
            this->selected[i][j] = false;
            this->legal_check = false;
            this->legal_squares[i][j] = true;
            this->highlights[i][j] = 0;
            for (int k=0; k < 9; k++) {
                this->pencil_marks[i][j][k] = false;
            }
            if (board[i][j] != 0) {
                this->started[i][j] = true;
            } else {
                this->started[i][j] = false;
            }
        }
    }

    this->won = false;

    this->default_box_color = sf::Color::White;
    this->win_box_color = sf::Color::Green;
    this->selected_box_color = sf::Color::Yellow;
    this->error_box_color = sf::Color::Red;
    this->default_text_color = sf::Color::Black;
    this->selected_text_color = sf::Color::Black;
    this->error_text_color = sf::Color::Black;
    this->started_text_color = sf::Color(150, 150, 150);
    this->started_selected_text_color = sf::Color(150, 150, 150);
    this->started_error_text_color = sf::Color(150, 150, 150);
    this->pencil_color = sf::Color(150, 150, 150);
    this->selected_highlighted_box_color = sf::Color(175, 175, 0);
    this->selected_error_box_color = sf::Color(255, 100, 100);

    this->highlight_colors.clear();
    this->highlight_colors.push_back(sf::Color(100, 255, 100)); // Light green
    this->highlight_colors.push_back(sf::Color(255, 165, 0)); // Orange
    this->highlight_colors.push_back(sf::Color::Magenta);
    this->highlight_colors.push_back(sf::Color::Cyan);
}

void SudokuBoard::set_board(int board[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            this->board[i][j] = board[i][j];
            this->legal_squares[i][j] = true;
            if (board[i][j] != 0) {
                this->started[i][j] = true;
            } else {
                this->started[i][j] = false;
            }
        }
    }
    this->legal_check = false;
}

void SudokuBoard::set_number_of_square(int x, int y, int number)
{
    this->board[x][y] = number;
    this->legal_check = false;
}

void SudokuBoard::select_square(int x, int y)
{
    this->selected[x][y] = true;
}

void SudokuBoard::deselect_square(int x, int y)
{
    this->selected[x][y] = false;
}

void SudokuBoard::deselect_all()
{
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            this->selected[i][j] = false;
        }
    }
}

void SudokuBoard::select_row(int row)
{
    for (int i = 0; i < 9; i++) {
        this->selected[i][row] = true;
    }
}

void SudokuBoard::select_column(int column)
{
    for (int i = 0; i < 9; i++) {
        this->selected[column][i] = true;
    }
}

void SudokuBoard::select_block(int block)
{
    int x = (block % 3) * 3;
    int y = (block / 3) * 3;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            this->selected[x + i][y + j] = true;
        }
    }
}

void SudokuBoard::insert_number_into_selected(int num)
{
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (this->selected[i][j] && !this->started[i][j]) {
                this->board[i][j] = num;
            }
        }
    }
    this->legal_check = false;
}

void SudokuBoard::remove_numbers_from_selected()
{
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (this->selected[i][j] && !this->started[i][j]) {
                this->board[i][j] = 0;
            }
        }
    }
    this->legal_check = false;
}

bool SudokuBoard::check_row(int x, int y)
{
    int row = y;
    // Check if number at xy is anywhere in row EXCEPT for xy
    for (int i = 0; i < 9; i++) {
        if (i != x) {
            if (this->board[i][row] == this->board[x][y]) {
                return false;
            }
        }
    }
    return true;
}

bool SudokuBoard::check_column(int x, int y)
{
    int column = x;
    // Check if number at xy is anywhere in column EXCEPT for xy
    for (int i = 0; i < 9; i++) {
        if (i != y) {
            if (this->board[column][i] == this->board[x][y]) {
                return false;
            }
        }
    }
    return true;
}

bool SudokuBoard::check_block(int x, int y)
{
    int block = (y / 3) * 3 + (x / 3);
    // Check if number at xy is anywhere in block EXCEPT for xy
    int x_start = (block % 3) * 3;
    int y_start = (block / 3) * 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i+x_start != x && j+y_start != y) {
                if (this->board[x_start + i][y_start + j] == this->board[x][y]) {
                    return false;
                }
            }
        }
    }
    return true;
}

void SudokuBoard::check_legality()
{
    int full_squares = 0;
    int legal_squares = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (this->board[i][j] != 0) {
                full_squares++;
                if (!this->check_row(i, j)) {
                    this->legal_squares[i][j] = false;
                }
                else if (!this->check_column(i, j)) {
                    this->legal_squares[i][j] = false;
                }
                else if (!this->check_block(i, j)) {
                    this->legal_squares[i][j] = false;
                }
                else {
                    this->legal_squares[i][j] = true;
                    legal_squares += 1;
                }
            } else {
                this->legal_squares[i][j] = true;
                legal_squares += 1;
            }
        }
    }
    if (full_squares == 81 && legal_squares == 81) {
        this->won = true;
    }
    this->legal_check = true;
}

void SudokuBoard::toggle_pencil_mark(int mark)
{
    // For every square, toggle mark mark if selected
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (this->selected[i][j]) {
                this->pencil_marks[i][j][mark] ^= true;
            }
        }
    }
    this->legal_check=false;
}

void SudokuBoard::remove_pencil_marks()
{
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (this->selected[i][j]) {
                for (int k = 0; k < 9; k++) {
                    this->pencil_marks[i][j][k] = false;
                }
            }
        }
    }
    this->legal_check=false;
}

void SudokuBoard::set_highlight(int high)
{
    // Set each selected cells' highlight to int
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (this->selected[i][j]) {
                this->highlights[i][j] = high;
            }
        }
    }
    this->legal_check = false;
}

void SudokuBoard::remove_highlight()
{
    // Set each selected cells' highlight to 0
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (this->selected[i][j]) {
                this->highlights[i][j] = 0;
            }
        }
    }
    this->legal_check = false;
}