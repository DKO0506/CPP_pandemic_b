#include "Board.hpp"
#include "Color.hpp"
#include "City.hpp"
#include <fstream>
#include <iostream>

using namespace pandemic;
using namespace std;

namespace pandemic
{
    Board::Board()
    {
        ifstream city{"cities_map.txt"};
        string name;
        string color;
        while (city >> name >> color)
        {
            City c_name = string_to_city.find(name)->second;
            _disease_level[c_name] = 0;
            Color c_color = string_to_color.find(color)->second;
            _color_associations[c_name] = c_color;
            string n;
            while (city.peek() != '\n' && city >> n )
            {
                _city_connections[c_name].insert(string_to_city.find(n)->second);
                n = "";
            }
        }
        city.close();
    }

    bool Board::is_clean() const
    {
        for (auto city : _disease_level)
        {
            if (city.second != 0)
            {
                return false;
            }
        }
        return true;
    }

    bool Board::is_cured(Color color) const
    {
        return _cures.find(color) != _cures.end();
    }

    bool Board::has_path(City a, City b) const
    {
        set temp = _city_connections.find(a)->second;
        return temp.find(b) != temp.end();
    }

    bool Board::has_station(City city) const
    {
        return _research_stations.find(city) != _research_stations.end();
    }

    void Board::add_cure(Color color)
    {
        _cures.insert(color);
    }
    void Board::add_station(City city)
    {
        _research_stations.insert(city);
    }
    void Board::remove_cures()
    {
        _cures.clear();
    }
    void Board::remove_stations()
    {
        _research_stations.clear();
    }
    int &Board::operator[](City city)
    {
        return _disease_level[city];
    }

    Color Board::get_Color(City city) const
    {
        return _color_associations.find(city)->second;
    }

    ostream &operator<<(std::ostream &out, Board &b)
    {

        out << "----------------------------------------    Pandemic Game   ----------------------------------------\n"
            << endl;

        for (auto city : b._disease_level)
        {
            string n = city_to_string.find(city.first)->second;
            int level = b[city.first];
            out << "City :" << n << ", Disease Level :" << level << endl;
        }
        out << "****************************************    Cure List   ****************************************\n"
            << endl;
        for (auto color : b._cures)
        {
            string c = color_to_string.find(color)->second;
            out << c << endl;
        }
        out << "\n\n************************************    Research Stations   ***********************************\n"
            << endl;
        for (auto res_station : b._research_stations)
        {
            string station = city_to_string.find(res_station)->second;
            out << station << endl;
        }
        out << "\n\n\n************************************ Game Over    ************************************" << endl;
        return out;
    }
};