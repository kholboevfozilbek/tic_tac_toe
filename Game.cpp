
#include "Game.hpp"

Game::Game() // initialization of all the tools and objects used in the game
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0 )
    {
        throw std::runtime_error("sdl2 could not be initialized! \n");
    }

    std::cout << "sdl2 is initialized successfully! \n";


    if(TTF_Init() == -1)
    {
        throw std::runtime_error("TTF could not be loaded! \n");
    }

    std::cout << "TTF is opened successfully! \n";

    font = TTF_OpenFont("assets/fonts/Handsome.ttf", 20);

    if(font == nullptr)
    {
        throw std::runtime_error("font could not be opened! \n");
    }

    std::cout << "Font is opened successfully! \n";

    ask_symbol_rect.set_dimensions(0, 0, 400, 150);
    option_X.set_dimensions(50, 150, 30, 30);
    option_O.set_dimensions(200, 150, 30, 30);

    info_board_rect.set_dimensions(0, 0, 500, 50);

    win_draw.set_dimensions(0, 0, 300, 50);


    // create main game window

    m_window = SDL_CreateWindow(
        "Tic Tac Toe",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WIDTH,
        HEIGHT,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );

    if(m_window == nullptr)
    {
        throw std::runtime_error("window could not be created! ");
    }

    std::cout << "window is created successfully! \n";


    // surface

    m_surface = SDL_GetWindowSurface(m_window);

    SDL_FillRect(m_surface, NULL, SDL_MapRGB(m_surface->format, 0, 0, 0));


    // create the main game renderer

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

    if(m_renderer == nullptr)
    {
        throw std::runtime_error("renderer could not be created! \n");
    }

    std::cout << "renderer is created successfully! \n";


    // generate the main game board

    if(!generate_board())
    {
        throw std::runtime_error("board could not be created! \n");
    }

    std::cout << "board is created successfully! \n";
}
    

Game::~Game() // proper cleanup of all the resources
{
    SDL_DestroyWindow(m_window);

    SDL_FreeSurface(m_surface);

    SDL_DestroyRenderer(m_renderer);

    SDL_Quit();
}
    

int Game::execute()
{

    ask_player_symbol();

    SDL_Delay(1000);

    while (running)
    {
        event_handler(m_event);

        if(!check_win_draw())
        {
            game_logic();
        }

        render();
    }
    
    return 0; // successfull termination of the program
}


void Game::event_handler(SDL_Event& m_event)
{
    while(SDL_PollEvent(&m_event))
    {
        if(m_event.type == SDL_QUIT)
        {
            running = false;
        }
    }
}


void Game::render()
{
    SDL_RenderClear(m_renderer);

    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

    if(win_flag)
    {
        render_win();
    }
    else if(draw_flag)
    {
        render_draw();
    }

    if(player.turn() && !win_flag)
    {
        render_info_board();
    }

    display_board();

    SDL_RenderPresent(m_renderer);
}


bool Game::check_win_draw()
{
    ///TODO: check for DRAW

    int counter = 0;

    for(int i=0; i<3; ++i)
    {
        for(int j=0; j<3; ++j)
        {
            if(!board[i][j].empty())
            {
                ++counter;
            }
        }
    }

    if(counter == 9)
    {
        /// it means all the rectangle in the board is full, hence draw
        draw_flag = true;

        return true;
    }


    ///TODO: check for WIN

    ///TODO: check for ROWWISE WIN CASES


    /// FIRST ROW

    if(board[0][0].symbol() != '\0')
    {
        if(board[0][0].symbol() == board[0][1].symbol() && board[0][1].symbol() == board[0][2].symbol())
        {
            winner_symbol = board[0][2].symbol();
            
            win_flag = true;

            std::cout << "first row win has been captured! \n";

            return true;
        }
    }


    /// SECOND ROW

    if(board[1][0].symbol() != '\0')
    {
        if(board[1][0].symbol() == board[1][1].symbol() && board[1][1].symbol() == board[1][2].symbol())
        {
            winner_symbol = board[1][2].symbol();
            
            win_flag = true;

            std::cout << "second row win has been captured! \n";

            return true;
        }
    }


    /// THIRD ROW

    if(board[2][0].symbol() != '\0')
    {
        if(board[2][0].symbol() == board[2][1].symbol() && board[2][1].symbol() == board[2][2].symbol())
        {
            winner_symbol = board[2][2].symbol();
            
            win_flag = true;

            std::cout << "third row win has been captured! \n";

            return true;
        }
    }


    ///TODO: check for COLUMNWISE WIN CASES

    /// FIRST COLOUMN

    if(board[0][0].symbol() != '\0')
    {
        if(board[0][0].symbol() == board[1][0].symbol() && board[1][0].symbol() == board[2][0].symbol())
        {
            winner_symbol = board[2][0].symbol();
            
            win_flag = true;

            std::cout << "first column win has been captured! \n";

            return true;
        }
    }


    /// SECOND COLOUMN

    if(board[0][1].symbol() != '\0')
    {
        if(board[0][1].symbol() == board[1][1].symbol() && board[1][1].symbol() == board[2][1].symbol())
        {
            winner_symbol = board[2][1].symbol();
            
            win_flag = true;

            std::cout << "second column win has been captured! \n";

            return true;
        }
    }


    /// THIRD COLOUMN

    if(board[0][2].symbol() != '\0')
    {
        if(board[0][2].symbol() == board[1][2].symbol() && board[1][2].symbol() == board[2][2].symbol())
        {
            winner_symbol = board[2][2].symbol();
            
            win_flag = true;

            std::cout << "third column win has been captured! \n";

            return true;
        }
    }


    ///TODO: check for DIAGONAL WIN CASES 

    /// FISRT DIAGONAL

    if(board[0][0].symbol() != '\0')
    {
        if(board[0][0].symbol() == board[1][1].symbol() && board[1][1].symbol() == board[2][2].symbol())
        {
            winner_symbol = board[2][2].symbol();
            
            win_flag = true;

            std::cout << "first diagonal win has been captured! \n";

            return true;
        }
    }


    /// SECOND DIAGONAL

    if(board[0][2].symbol() != '\0')
    {
        if(board[0][2].symbol() == board[1][1].symbol() && board[1][1].symbol() == board[2][0].symbol())
        {
            winner_symbol = board[2][0].symbol();
            
            win_flag = true;

            std::cout << "second diagonal win has been captured! \n";

            return true;
        }
    }

    // if we hit here, it means there was no draw and no win case, so we need to continue the game

    return false;
}


void Game::game_logic()
{
    if(player.turn())
    {
        listen_player_input();
    }
    else
    {
        ///TODO: add here AI_input feature
        // temporarily we take player input in all case, but in future this will change to AI
        listen_player_input();
    }
}

    
void Game::listen_player_input() // today we will implement this feature
{
    SDL_Point mousePosition;

    mousePosition.x = m_event.motion.x;
    mousePosition.y = m_event.motion.y;

    for(int i=0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            if(SDL_PointInRect(&mousePosition, board[i][j].rect()))
            {
                if(board[i][j].empty())
                {
                    // player can only place his move to rectangles thats empty!

                    if(m_event.button.type == SDL_MOUSEBUTTONDOWN)
                    {
                        switch (player.symbol())
                        {
                        case 'X':
                            board[i][j].set_surface("assets/images/x.bmp", m_renderer);
                            
                            SDL_RenderCopy(m_renderer, board[i][j].texture(), NULL, board[i][j].rect());

                            board[i][j].set_empty(false);

                            board[i][j].set_symbol('X');

                            ///TODO: here after player places his move, we should put player.turn to false
                            /// and give the move to AI

                            player.set_turn(false);

                            break;

                        case 'O':

                            board[i][j].set_surface("assets/images/o.bmp", m_renderer);

                            SDL_RenderCopy(m_renderer, board[i][j].texture(), NULL, board[i][j].rect());

                            board[i][j].set_empty(false);

                            board[i][j].set_symbol('O');

                            player.set_turn(false);
                        
                        default:
                            break;
                        }
                    }
                }
            }
        }
    }
}

// helper functions

bool Game::generate_board()
{
    int rect_width = WIDTH / 3;
    int rect_height = HEIGHT / 3;

    int board_x = WIDTH / 2 - rect_width * 3 / 2;
    int board_y = (HEIGHT - 100) / 2 -rect_height * 3 / 2 + 100;


    for(int row = 0; row < 3; ++row)
    {
        for(int col = 0; col < 3; ++col)
        {
            board[row][col].set_dimensions(board_x + col * rect_width, 
            board_y + row * rect_height, rect_width, rect_height);
        }
    }

    return true;
}


void Game::display_board()
{
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            SDL_RenderCopy(m_renderer, board[i][j].texture(), NULL, board[i][j].rect());
            SDL_RenderDrawRect(m_renderer, board[i][j].rect());
        }
    }

    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}


void Game::ask_player_symbol()
{
    while(player.symbol() == '\0')
    {
        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

        render_ask_player_symbol_rect();

        render_option_X();

        render_option_O();

        while(SDL_PollEvent(&m_event))
        {
            if(m_event.type == SDL_QUIT)
            {
                break;    
            }
        }

        listen_user_input();

        SDL_RenderPresent(m_renderer);
    }
}

void Game::render_ask_player_symbol_rect()
{
    text_surface = TTF_RenderText_Solid(font, "C h o o s e  a  s y m b o l", {0, 255, 0});
    text_texture = SDL_CreateTextureFromSurface(m_renderer, text_surface);

    SDL_RenderCopy(m_renderer, text_texture, NULL, ask_symbol_rect.rect());
}

void Game::render_option_X()
{
    text_surface = TTF_RenderText_Solid(font, "X", {0, 255, 0});

    text_texture = SDL_CreateTextureFromSurface(m_renderer, text_surface);

    SDL_RenderCopy(m_renderer, text_texture, NULL, option_X.rect());
}

void Game::render_option_O()
{
    text_surface = TTF_RenderText_Solid(font, "O", {0, 255, 0});

    text_texture = SDL_CreateTextureFromSurface(m_renderer, text_surface);

    SDL_RenderCopy(m_renderer, text_texture, NULL, option_O.rect());
}

void Game::render_info_board()
{
    std::string message = "Y o u r  t u r n: ";

    message += player.symbol();

    text_surface = TTF_RenderText_Solid(font, message.c_str(), {0, 255, 0});

    text_texture = SDL_CreateTextureFromSurface(m_renderer, text_surface);

    SDL_RenderCopy(m_renderer, text_texture, NULL, info_board_rect.rect());
}


void Game::render_win()
{
    std::string message = "W I N N E R :  ";

    message += winner_symbol;

    text_surface = TTF_RenderText_Solid(font, message.c_str(), {0, 255, 0});

    text_texture = SDL_CreateTextureFromSurface(m_renderer, text_surface);

    SDL_RenderCopy(m_renderer, text_texture, NULL, win_draw.rect());
}


void Game::render_draw()
{
    std::string message = "D R A W  !";

    text_surface = TTF_RenderText_Solid(font, message.c_str(), {0, 255, 0});

    text_texture = SDL_CreateTextureFromSurface(m_renderer, text_surface);

    SDL_RenderCopy(m_renderer, text_texture, NULL, win_draw.rect());
}


void Game::listen_user_input()
{
    SDL_Point mouse_position;

    mouse_position.x = m_event.motion.x;
    mouse_position.y = m_event.motion.y;

    if(SDL_PointInRect(&mouse_position, option_X.rect()))
    {
        if(m_event.button.type == SDL_MOUSEBUTTONDOWN)
        {
            player.set_symbol('X');
        }

    }
    else if(SDL_PointInRect(&mouse_position, option_O.rect()))
    {
        if(m_event.button.type == SDL_MOUSEBUTTONDOWN)
        {
            player.set_symbol('O');
        }
    }

    player.set_turn(true);
}

