#pragma once
#include <SFML/Graphics.hpp>
#include <array>

sf::Color getColor(size_t index)
{
  static std::array ballColors = {sf::Color::Red, sf::Color::Blue, sf::Color::Yellow, sf::Color::Green};
  if (index >= ballColors.size())
    throw std::out_of_range("ratio illegal\n");
  return ballColors[index];
}