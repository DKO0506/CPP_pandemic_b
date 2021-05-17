#include "Player.hpp"

#pragma once



namespace pandemic{
    class Scientist : public Player{
    private:
        int min_cards;
    public:

        Scientist(Board& board, City city, int v) : Player(board,city),min_cards(v){}

        std::string role() const {
            return "Scientist";
        }
        Player& discover_cure(Color color){
            if(!(board.has_station(starting_point))){
                throw std::invalid_argument("No research station found in this city");
            }
            if(board.is_cured(color)){
                return *this;
            }
            int count = 0;
            std::set<City>deck;
            for(auto c_card : cards){
                if (board.get_Color(c_card) == color){
                    count++;
                    deck.insert(c_card);
                    if(count == min_cards){
                        break;
                    }
                }
            }
            if (count == min_cards){
                board.add_cure(color);
                for(auto city : deck){
                    cards.erase(city);
                }
            } else{
                throw std::invalid_argument("There are not enough card");
            }
            return *this;
        }
    };
}