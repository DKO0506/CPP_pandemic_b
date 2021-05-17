#include "Player.hpp"

#pragma once

namespace pandemic
{
    class Researcher : public Player
    {
    private:
        const int min_cards = 5;

    public:
        Researcher(Board &board, City city) : Player(board, city) {}

        std::string role() const
        {
            return "Researcher";
        }

        Player &discover_cure(Color color)
        {
            if (board.is_cured(color))
            {
                return *this;
            }
            int count = 0;
            std::set<City> deck;
            for (auto c_card : cards)
            {
                if (board.get_Color(c_card) == color)
                {
                    count++;
                    deck.insert(c_card);
                    if (count == min_cards)
                    {
                        break;
                    }
                }
            }
            if (count == min_cards)
            {
                board.add_cure(color);
                for (auto city : deck)
                {
                    cards.erase(city);
                }
            }
            else
            {
                throw std::invalid_argument("There are not enough card");
            }
            return *this;
        }
    };
}