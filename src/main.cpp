#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <string>
#include <memory>
#include <math.h>
#include <stdlib.h>
#include "sudoku.h"
#include "sudokufile.h"

using namespace sf;
using namespace sudoku;

#define SUDOKU_X 20
#define SUDOKU_Y 60

Color invert(Color color)
{
    return Color(255 - color.r, 255 - color.g, 255 - color.b);
}

int main()
{
    srand(time(NULL));
    RenderWindow window(VideoMode(490, 520), "Sudoku Game", Style::Close | Style::Titlebar);
    RenderTexture boardTexture;
    Sprite boardSprite;
    boardTexture.create(450, 450);
    std::unique_ptr<SudokuLibrary> library(new SudokuLibrary());

    library->load_library_file("assets/games.sdm");

    int rand_game = rand() % library->files.size();

    SudokuFile gameFile = library->getsudokufile(rand_game);
    SudokuBoard board = gameFile.board;

    std::cout << "Game: " << rand_game << std::endl;

    Texture texture;
    if (!texture.loadFromFile("assets/tile.png"))
        return EXIT_FAILURE;
    Sprite sprite(texture);

    Font font;
    if (!font.loadFromFile("assets/Nunito-ExtraBold.ttf"))
        return EXIT_FAILURE;

    RectangleShape big_lines_horiz(Vector2f(texture.getSize().x * 9, 6));
    RectangleShape big_lines_vert(Vector2f(6, texture.getSize().y * 9));
    Text fps_text;

    Text tile_text[9];
    Text pencil_text[9];
    Text difficulty_text[3];

    int selected_number = 0;


    for (int i=1; i<10; i++)
    {
        tile_text[i-1].setFont(font);
        tile_text[i-1].setCharacterSize(42);
        tile_text[i-1].setFillColor(Color::Black);
        tile_text[i-1].setString(std::to_string(i));
    }

    for (int i=1; i<10; i++)
    {
        pencil_text[i-1].setFont(font);
        pencil_text[i-1].setCharacterSize(10);
        pencil_text[i-1].setFillColor(Color(150, 150, 150));
        pencil_text[i-1].setString(std::to_string(i));
    }

    for (int i=0; i<3; i++)
    {
        difficulty_text[i].setFont(font);
        difficulty_text[i].setCharacterSize(30);
    }

    difficulty_text[0].setString("Easy");
    difficulty_text[0].setFillColor(Color::Green);
    difficulty_text[1].setString("Medium");
    difficulty_text[1].setFillColor(Color::Yellow);
    difficulty_text[2].setString("Hard");
    difficulty_text[2].setFillColor(Color::Red);

    big_lines_horiz.setFillColor(Color::Black);
    big_lines_vert.setFillColor(Color::Black);

    bool board_changed = true;

    bool mouse_down = false;

    while (window.isOpen())
    {

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            } else if (event.type == Event::MouseButtonPressed)
            {
                mouse_down = true;
                if (event.mouseButton.button == Mouse::Left)
                {
                    board.deselect_all();
                }
                int x = event.mouseButton.x;
                int y = event.mouseButton.y;
                x -= SUDOKU_X;
                y -= SUDOKU_Y;
                x /= texture.getSize().x;
                y /= texture.getSize().y;
                x = floor(x);
                y = floor(y);
                if (x >= 0 && x < 9 && y >= 0 && y < 9)
                {
                    board.select_square(x, y);
                    board_changed = true;
                }
            } else if (event.type == Event::MouseButtonReleased)
            {
                mouse_down = false;
            } else if (event.type == Event::MouseMoved)
            {
                if (mouse_down) {
                    int x = event.mouseMove.x;
                    int y = event.mouseMove.y;
                    x -= SUDOKU_X;
                    y -= SUDOKU_Y;
                    x /= texture.getSize().x;
                    y /= texture.getSize().y;
                    x = floor(x);
                    y = floor(y);
                    if (x >= 0 && x < 9 && y >= 0 && y < 9)
                    {
                        board.select_square(x, y);
                        board_changed = true;
                    }
                }
            } else if (event.type == Event::KeyPressed)
            {
                bool change_number = false;
                if (!event.key.shift) {
                    if (event.key.code == Keyboard::Num1)
                    {
                        selected_number = 1;
                        change_number = true;
                    } else if (event.key.code == Keyboard::Num2)
                    {
                        selected_number = 2;
                        change_number = true;
                    } else if (event.key.code == Keyboard::Num3)
                    {
                        selected_number = 3;
                        change_number = true;
                    } else if (event.key.code == Keyboard::Num4)
                    {
                        selected_number = 4;
                        change_number = true;
                    } else if (event.key.code == Keyboard::Num5)
                    {
                        selected_number = 5;
                        change_number = true;
                    } else if (event.key.code == Keyboard::Num6)
                    {
                        selected_number = 6;
                        change_number = true;
                    } else if (event.key.code == Keyboard::Num7)
                    {
                        selected_number = 7;
                        change_number = true;
                    } else if (event.key.code == Keyboard::Num8)
                    {
                        selected_number = 8;
                        change_number = true;
                    } else if (event.key.code == Keyboard::Num9)
                    {
                        selected_number = 9;
                        change_number = true;
                    } else if (event.key.code == Keyboard::BackSpace)
                    {
                        board.remove_numbers_from_selected();
                    } else if (event.key.code == Keyboard::Q)
                    {
                        board.remove_highlight();
                    } else if (event.key.code == Keyboard::W)
                    {
                        board.set_highlight(1);
                    } else if (event.key.code == Keyboard::E)
                    {
                        board.set_highlight(2);
                    } else if (event.key.code == Keyboard::R)
                    {
                        board.set_highlight(3);
                    } else if (event.key.code == Keyboard::T)
                    {
                        board.set_highlight(4);
                    }
                    if (change_number)
                    {
                        board.insert_number_into_selected(selected_number);
                    }
                } else {
                    if (event.key.code > 26 && event.key.code < 36)
                    {
                        selected_number = event.key.code - 27;
                        board.toggle_pencil_mark(selected_number);
                    } else if (event.key.code == Keyboard::BackSpace)
                    {
                        board.remove_pencil_marks();
                    }
                }
            }
        }

        if (!board.legal_check) {
            board.check_legality();
            board_changed = true;
        }

        window.clear(Color(200, 200, 200));


        if (board_changed)
        {

            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    sprite.setPosition(i * 50, j * 50);
                    if (board.won)
                    {
                        sprite.setColor(board.win_box_color);
                    } else if (board.selected[i][j])
                    {
                        if (!board.legal_squares[i][j])
                        {
                            sprite.setColor(board.selected_error_box_color);
                        } else if (board.highlights[i][j]!=0) {
                            sprite.setColor(board.selected_highlighted_box_color);
                        } else {
                            sprite.setColor(board.selected_box_color);
                        }
                    } else if (!board.legal_squares[i][j])
                    {
                        sprite.setColor(board.error_box_color);
                    } else if (board.highlights[i][j]!=0)
                    {
                        sprite.setColor(board.highlight_colors[board.highlights[i][j]-1]);
                    } else
                    {
                        sprite.setColor(board.default_box_color);
                    }
                    boardTexture.draw(sprite);
                }
            }

            for (int i=0; i<9; i++)
            {
                for (int j=0; j<9; j++)
                {
                    if (board.board[i][j] != 0)
                    {
                        tile_text[board.board[i][j] - 1].setPosition(i * 50 + 10, j * 50);
                        if (board.started[i][j]) {
                            if (board.selected[i][j])
                            {
                                tile_text[board.board[i][j] - 1].setFillColor(board.started_selected_text_color);
                            } else if (!board.legal_squares[i][j])
                            {
                                tile_text[board.board[i][j] - 1].setFillColor(board.started_error_text_color);
                            } else
                            {
                                tile_text[board.board[i][j] - 1].setFillColor(board.started_text_color);
                            }
                        } else {
                            if (board.selected[i][j])
                            {
                                tile_text[board.board[i][j] - 1].setFillColor(board.selected_text_color);
                            } else if (!board.legal_squares[i][j])
                            {
                                tile_text[board.board[i][j] - 1].setFillColor(board.error_text_color);
                            } else
                            {
                                tile_text[board.board[i][j] - 1].setFillColor(board.default_text_color);
                            }
                        }
                        boardTexture.draw(tile_text[board.board[i][j] - 1]);
                    } else {
                        for (int k=0; k<9; k++) {
                            bool is_pencil_enabled = board.pencil_marks[i][j][k];
                            if (is_pencil_enabled) {
                                pencil_text[k].setPosition(i * 50 + (15 * (k % 3)) + 5, j * 50 + (15 * (k / 3)) + 5);
                                pencil_text[k].setFillColor(board.pencil_color);
                                boardTexture.draw(pencil_text[k]);
                            }
                        }
                    }
                }
            }

            boardTexture.display();

            boardSprite.setTexture(boardTexture.getTexture());
            boardSprite.setPosition(Vector2f(SUDOKU_X, SUDOKU_Y));

            window.draw(boardSprite);

            for (int i=0; i<12; i+=3)
            {
                big_lines_horiz.setPosition(SUDOKU_X, i * 50 - 3 + SUDOKU_Y);
                big_lines_vert.setPosition(i * 50 - 3 + SUDOKU_X, SUDOKU_Y);
                window.draw(big_lines_horiz);
                window.draw(big_lines_vert);
            }

            if (rand_game < library->files.size()/3) {
                difficulty_text[0].setPosition(Vector2f(SUDOKU_X + 225 - difficulty_text[0].getGlobalBounds().width/2, 10));
                window.draw(difficulty_text[0]);
            } else if (rand_game < library->files.size()/3*2) {
                difficulty_text[1].setPosition(Vector2f(SUDOKU_X + 225 - difficulty_text[1].getGlobalBounds().width/2, 10));
                window.draw(difficulty_text[1]);
            } else {
                difficulty_text[2].setPosition(Vector2f(SUDOKU_X + 225 - difficulty_text[2].getGlobalBounds().width/2, 10));
                window.draw(difficulty_text[2]);
            }

            window.display();

            board_changed = false;

        }

    }
}