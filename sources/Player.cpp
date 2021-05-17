#include "Player.hpp"

using namespace std;
using namespace pandemic;

const int min_cards = 5;

Player& Player::drive(City dest) {
    if (dest == starting_point) {
        throw invalid_argument("This your current position");
    }
    if (!(board.has_path(starting_point, dest))) {
        throw invalid_argument("There's no path between those cities!");
    }
    starting_point = dest;
    return *this;
}

Player& Player::fly_direct(City dest) {
    if (dest == starting_point) {
        throw invalid_argument("This your current position");
    }
    auto tmp = cards.find(dest);
    if (tmp == cards.end()) {
        throw invalid_argument("The player doesn't possess this card!");
    }
    starting_point = dest;
    cards.erase(tmp);
    return *this;
}

Player &Player::fly_charter(City dest) {
    if (dest == starting_point) {
        throw invalid_argument("This your current position");
    }
    auto tmp = cards.find(starting_point);
    if (tmp == cards.end()) {
        throw invalid_argument("The player doesn't possess this card!");
    }
    starting_point = dest;
    cards.erase(tmp);
    return *this;
}

Player& Player::fly_shuttle(City dest) {
    if (dest == starting_point) {
        throw invalid_argument("This your current position");
    }
    if (board.has_station(starting_point) && board.has_station(dest)) {
        starting_point = dest;
    } else {
        throw invalid_argument("there is no research station in these cities!");
    }
    return *this;
}

Player& Player::build() {
    if (!(board.has_station(starting_point))) {
        if (cards.find(starting_point) != cards.end()) {
            board.add_station(starting_point);
            cards.erase(starting_point);
        } else {
            throw invalid_argument("The player doesn't possess this card!");
        }
    }
    return *this;
}

Player& Player::discover_cure(Color color) {
    if (board.is_cured(color)) {
        return *this;
    }
    if (!(board.has_station(starting_point))) {
        throw invalid_argument("No research station found in this city");
    }

    int count = 0;
    set <City> card_deck;
    for (auto city_card : cards) {
        if (board.get_Color(city_card) == color) {
            count++;
            card_deck.insert(city_card);
            if (count == min_cards) {
                break;
            }
        }
    }
    if (count == min_cards) {
        board.add_cure(color);
        for (auto city : card_deck) {
            cards.erase(city);
        }
    } else {
        throw invalid_argument("There are not enough card");
    }
    return *this;
}

Player& Player::treat(City city) {
    if (city == starting_point) {
        if (board[city] > 0) {
            if (board.is_cured(board.get_Color(city))) {
                board[city] = 0;
            } else {
                board[city] -= 1;
            }
        } else {
            throw invalid_argument("Disease level in this city is 0!");
        }
    } else {
        throw invalid_argument("You're not located in this city");
    }
    return *this;
}

Player& Player::take_card(City city) {
    cards.insert(city);
    return *this;
}

string Player::role() const {
    return "";
}

void Player::remove_cards() {
    cards.clear();
}