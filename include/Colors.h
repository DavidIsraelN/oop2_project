#pragma once
#include <SFML/Graphics.hpp>
#include <array>

/* ----------------------------------------------------------
 * This is for the colors of the game.
 */

const auto semi_transparent = sf::Color(0, 0, 0, 70);

sf::Color getColor(size_t);
