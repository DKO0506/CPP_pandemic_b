#include "Player.hpp"

#pragma once
namespace pandemic {
    class Dispatcher : public Player {
    public:
        Dispatcher(Board &board, City city) : Player(board, city) {}

        std::string role() const {
            return "Dispatcher";
        }

        Player& fly_direct(City dest) {
            if (dest == starting_point) {
                throw std::invalid_argument("This your current position");
            }
            if (board.has_station(starting_point)) {
                starting_point = dest;
            } else {
                return Player::fly_direct(dest);
            }
            return *this;
        }
    };
}