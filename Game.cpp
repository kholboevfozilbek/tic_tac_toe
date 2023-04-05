
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

    display_board();

    SDL_RenderPresent(m_renderer);
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

    SDL_RenderCopy(m_renderer, text_texture, NULL, option_X.rect());
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

