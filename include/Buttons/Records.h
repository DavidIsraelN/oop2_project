#pragma once
#include "Button.h"

/*
 * class for records button and screen (inherited from button class).
 */

class Records : public Button
{
public:
  Records(float, float, const sf::Vector2f&, const sf::Vector2f&);
  Action action(sf::RenderWindow&) override;
  size_t getRecord() const;
  void updateRecord(size_t);

private:
  void loadRecords();
  void drawRecords(sf::RenderWindow&) const;

  size_t m_record;
  sf::Text m_text_title;
  std::unique_ptr<Button> m_back;
};
