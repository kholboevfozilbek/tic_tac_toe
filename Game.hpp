
#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Rectangle.hpp"
#include "Player.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

class Game
{

public:
    Game(); // initialization of all the tools and objects used in the game

    ~Game(); // proper cleanup of all the resources

    int execute();

    void event_handler(SDL_Event& m_event);

    void render();


    void game_logic();

    void listen_player_input(); // today we will implement this feature

    void AI_input(); // upcoming video!

    bool check_win_draw();


    // helper functions

    bool generate_board();

    void display_board();


    void ask_player_symbol();

    void render_ask_player_symbol_rect();

    void render_option_X();

    void render_option_O();

    void render_info_board();

    void render_win();

    void render_draw();

    void listen_user_input();


private:
    
    // game window related attributes

    const int WIDTH = 900;
    const int HEIGHT = 900;

    SDL_Window* m_window = nullptr;

    SDL_Surface* m_surface = nullptr;

    SDL_Renderer* m_renderer = nullptr;

    SDL_Event m_event;


    TTF_Font* font = nullptr;

    Rectangle ask_symbol_rect;

    Rectangle option_X;

    Rectangle option_O;

    Rectangle info_board_rect;

    SDL_Surface* text_surface = nullptr;

    SDL_Texture* text_texture = nullptr;

    // game logic related attributes

    bool running = true;

    bool win_flag = false;

    bool draw_flag = false;

    Rectangle win_draw;

    char winner_symbol = '\0';

    Rectangle board[3][3];

    Player player;

};



#endif