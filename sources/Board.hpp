#pragma once

#include <string>
#include <map>
#include <set>
#include "City.hpp"
#include "Color.hpp"
#include <iostream>

namespace pandemic
{
    class Board
    {
    private:
        std::map<City, std::set<City>> _city_connections;
        std::map<City, Color> _color_associations;
        std::map<City, int> _disease_level;
        std::set<Color> _cures;
        std::set<City> _research_stations;

    public:
        Board();
        int &operator[](City city);
        bool is_clean() const;
        bool is_cured(Color color) const;
        bool has_station(City city) const;
        bool has_path(City a, City b) const;

        void add_cure(Color color);
        void add_station(City city);
        void remove_cures();
        void remove_stations();
        Color get_Color(City city) const;

        friend std::ostream &operator<<(std::ostream &out, Board &b);
    };

}