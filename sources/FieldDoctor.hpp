#include "Player.hpp"
#pragma once

namespace pandemic
{
    class FieldDoctor : public Player
    {
    public:
        FieldDoctor(Board &board, City city) : Player(board, city) {}
        std::string role() const{
            return "FieldDoctor";
        }
        Player &treat(City city){
            if (city == starting_point || board.has_path(starting_point, city))
            {
                if (board[city] > 0)
                {
                    if (board.is_cured(board.get_Color(city)))
                    {
                        board[city] = 0;
                    }
                    else
                    {
                        board[city] = board[city] - 1;
                    }
                }
                else
                {
                    throw std::invalid_argument("Disease level in this city is 0!");
                }
            }
            else
            {
                throw std::invalid_argument("You're not located in this city or not even adjacent to it !");
            }
            return *this;
        }
    };
}