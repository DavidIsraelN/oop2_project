#pragma once
#include <SFML/Graphics.hpp>
#include <array>

const auto semi_transparent = sf::Color(0, 0, 0, 70);
const auto brown = sf::Color(153, 150, 141);

sf::Color getColor(size_t);
