

#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player
{

public:
    Player() = default;

    ~Player()
    {

    }

    char symbol()
    {
        return m_symbol;
    }

    bool turn()
    {
        return m_symbol;
    }

    void set_symbol(char ch)
    {
        m_symbol = ch;
    }

    void set_turn(bool turn)
    {
        m_turn = turn;
    }

private:
    
    char m_symbol = '\0';

    bool m_turn = true;
};


#endif