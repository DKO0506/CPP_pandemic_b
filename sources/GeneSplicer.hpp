#include "Player.hpp"

#pragma once


namespace pandemic
{
 class GeneSplicer : public Player{
    private:
        const int min_cards = 5;

    public:
        GeneSplicer(Board &board, City city) : Player(board, city) {}

        std::string role() const
        {
            return "GeneSplicer";
        }
        Player &discover_cure(Color color)
        {
            if (!(board.has_station(starting_point)))
            {
                throw std::invalid_argument("No research station found in this city");
            }
            if (board.is_cured(color))
            {
                return *this;
            }

            int count = 0;
            std::set<City> deck;
            if (cards.size() >= min_cards)
            {
                for (City c_card : cards)
                {
                    count++;
                    deck.insert(c_card);
                    if (count == min_cards)
                    {
                        break;
                    }
                }
                for (City c_card : deck)
                {
                    cards.erase(c_card);
                }
                board.add_cure(color);
            }
            else
            {
                throw std::invalid_argument("There are not enough card");
            }
            return *this;
        }
    };
}