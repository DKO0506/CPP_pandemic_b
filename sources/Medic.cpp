#include "Medic.hpp"

using namespace std;
using namespace pandemic;

Player &Medic::drive(City city) {
    if (city == starting_point) {
        throw invalid_argument("This your current position");
    }
    if (board.is_cured(board.get_Color(city))) {
        board[city] = 0;
    }
    Player::drive(city);
    return *this;
}

Player &Medic::fly_direct(City city) {
    if (city == starting_point) {
        throw invalid_argument("This your current position");
    }
    if (board.is_cured(board.get_Color(city))) {
        board[city] = 0;
    }
    Player::fly_direct(city);
    return *this;
}

Player &Medic::fly_charter(City city) {
    if (city == starting_point) {
        throw invalid_argument("This your current position");
    }
    if (board.is_cured(board.get_Color(city))) {
        board[city] = 0;
    }
    Player::fly_charter(city);
    return *this;
}

Player &Medic::fly_shuttle(City city) {
    if (city == starting_point) {
        throw invalid_argument("This your current position");
    }
    if (board.is_cured(board.get_Color(city))) {
        board[city] = 0;
    }
    Player::fly_shuttle(city);
    return *this;
}

Player &Medic::discover_cure(Color color) {
    Player::discover_cure(color);
    board[starting_point] = 0;
    return *this;
}

Player &Medic::treat(City city) {
    if (city == starting_point) {
        if (board[city] > 0) {
            board[city] = 0;
        } else {
            throw invalid_argument("Disease level in this city is 0!");
        }

    } else {
        throw invalid_argument("You're not located in this city");
    }
    return *this;
}