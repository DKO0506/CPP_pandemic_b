#include "Board.hpp"
#include "City.hpp"
#include <set>

#pragma once

namespace pandemic{

    class Player{

    protected:
        Board &board;
        std::set<City> cards;
        City starting_point;

    public:
        Player(Board& board, City city) : board(board), starting_point(city) {}
        virtual Player& drive(City dest);
        virtual Player& fly_direct(City dest);
        virtual Player& fly_charter(City dest);
        virtual Player& fly_shuttle(City dest);
        virtual Player& build();
        virtual Player& discover_cure(Color color);
        virtual Player& treat(City city);
        Player& take_card(City city);
        virtual std::string role() const;
        void remove_cards();
    };
}