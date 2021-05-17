#include "Player.hpp"

#pragma once


namespace pandemic {
    class Virologist : public Player {
    public:
        Virologist(Board &board, City city) : Player(board, city) {}

        std::string role() const {
            return "Virologist";
        }

        Player &treat(City city) {
            if (city == starting_point) {
                Player::treat(city);
            } else {
                if (cards.find(city) != cards.end()) {
                    if (board[city] > 0) {
                        if (board.is_cured(board.get_Color(city))) {
                            board[city] = 0;
                        } else {
                            board[city] -= 1;
                        }
                        cards.erase(city);
                    } else {
                        throw std::invalid_argument("Disease level in this city is 0!");
                    }
                } else {
                    throw std::invalid_argument("The player doesn't possess this card!");
                }
            }
            return *this;
        }
    };
}