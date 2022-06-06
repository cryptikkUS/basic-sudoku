#pragma once

#ifndef CRYPTIKK_SUDOKU_H
#define CRYPTIKK_SUDOKU_H

#include <SFML/Graphics.hpp>
#include <vector>

namespace sudoku {

    class SudokuBoard {
        public:
            SudokuBoard();
            SudokuBoard(int[9][9]);

            void set_board(int[9][9]);

            void set_number_of_square(int, int, int);

            void select_square(int, int);
            void deselect_square(int, int);
            void deselect_all();

            void select_row(int);
            void select_column(int);
            void select_block(int);

            void insert_number_into_selected(int);
            void remove_numbers_from_selected();

            void check_legality();
            bool check_row(int, int);
            bool check_column(int, int);
            bool check_block(int, int);

            void toggle_pencil_mark(int);
            void remove_pencil_marks();

            void set_highlight(int);
            void remove_highlight();

            int board[9][9];
            bool pencil_marks[9][9][9];
            bool legal_check;
            bool won;
            bool legal_squares[9][9];
            bool selected[9][9];
            bool started[9][9];
            int highlights[9][9];

            std::vector<sf::Color> highlight_colors;
            sf::Color selected_highlighted_box_color;
            sf::Color selected_error_box_color;
            sf::Color default_box_color;
            sf::Color selected_box_color;
            sf::Color error_box_color;
            sf::Color win_box_color;
            sf::Color default_text_color;
            sf::Color selected_text_color;
            sf::Color error_text_color;
            sf::Color started_text_color;
            sf::Color started_selected_text_color;
            sf::Color started_error_text_color;
            sf::Color pencil_color;
    };
}

#endif