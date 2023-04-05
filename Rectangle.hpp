
#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <SDL2/SDL.h>
#include <stdexcept>

class Rectangle
{

public:
    Rectangle() = default;

    ~Rectangle()
    {

    }


    bool empty()
    {
        return m_empty;
    }

    char symbol()
    {
        return m_symbol;
    }

    const SDL_Rect* rect()
    {
        return &m_rectangle;
    }

    SDL_Texture* texture()
    {
        return m_texture;
    }

    void set_dimensions(int x, int y, int w, int h)
    {
        m_rectangle.x = x;
        m_rectangle.y = y;
        m_rectangle.w = w;
        m_rectangle.h = h;
    }

    void set_surface(const char* filepath, SDL_Renderer* renderer)
    {
        m_surface = SDL_LoadBMP(filepath);

        m_texture = SDL_CreateTextureFromSurface(renderer, m_surface);
    }

private:
    
    SDL_Rect m_rectangle;
    
    SDL_Surface* m_surface = nullptr;

    SDL_Texture* m_texture = nullptr;

    bool m_empty = true;

    char m_symbol = '\0';
};


#endif