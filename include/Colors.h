#pragma once
#include <SFML/Graphics.hpp>
#include <array>

/* ----------------------------------------------------------
 * This is for the colors of the game.
 */

const auto semi_transparent = sf::Color(0, 0, 0, 70);
const auto main_beckground = sf::Color::Cyan;

sf::Color getColor(size_t);
