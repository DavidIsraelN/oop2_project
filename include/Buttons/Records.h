#pragma once
#include "Button.h"
#include <map>

/* ----------------------------------------------------------
 * class for records button and screen (inherited from button class).
 */

class Records : public Button
{
public:
  Records(float, float, const sf::Vector2f&, const sf::Vector2f&);
  Action action(sf::RenderWindow&) override;

private:
  void backToStart();
  void loadRecords(sf::RenderWindow&);
  void drawRecords(sf::RenderWindow&) const;

  std::fstream& m_file_records;
  std::multimap<size_t, std::string> m_records;
  sf::Text m_txt_title, m_txt_records;
  std::unique_ptr<Button> m_back;
};
