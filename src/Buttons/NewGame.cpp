#include "Buttons/NewGame.h"
#include "Buttons/Back.h"
#include "Buttons/ChooseLevel.h"
#include "ResourcesManager.h"
#include <algorithm>

//----------------------------------------------------------
NewGame::NewGame(float width, float height, const sf::Vector2f& size, const sf::Vector2f& position)
  :Button(size, position, "NEW GAME"),
  m_text_title(sf::Text("CHOOSE  LEVEL", 
    ResourceManager::Resource().getFont() , height / 6))
{
  buildLevels(width, height);
}

//----------------------------------------------------------
void NewGame::drawLevels(sf::RenderWindow& window) const
{
  window.clear(sf::Color::Cyan);
  window.draw(m_text_title);
  std::for_each(m_buttons.begin(), m_buttons.end(), [&window](auto& button) { button->draw(window); });
  window.display();
}

//----------------------------------------------------------
Action NewGame::action(sf::RenderWindow& window)
{
  drawLevels(window);

  while (window.isOpen())
  {
    if (auto event = sf::Event{}; window.waitEvent(event))
      switch (event.type)
      {
      case sf::Event::Closed:
        window.close();
        break;

      case sf::Event::MouseButtonReleased:
        auto loc = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
        for (auto &button : m_buttons)
          if (button->clickMe(loc)) return button->action(window);
      }
  }
  return getAction();
}

//----------------------------------------------------------
void NewGame::buildLevels(float width, float height)
{
  m_text_title.setFillColor(sf::Color::Black);
  m_text_title.setPosition(width / 2, height / 5);
  m_text_title.setOrigin(m_text_title.getGlobalBounds().width / 2,
                         m_text_title.getGlobalBounds().height / 2);
  m_text_title.setStyle(sf::Text::Underlined);

  m_buttons.emplace_back(std::make_unique<ChooseLevel>(sf::Vector2f(width / 3, height / 7),
    sf::Vector2f(width / 2 , 5.4 * height / 12), Action::LEVEL1));

  m_buttons.emplace_back(std::make_unique<ChooseLevel>(sf::Vector2f(width / 3 , height / 7),
    sf::Vector2f(width / 2 , 7.7 * height / 12), Action::LEVEL2));

  m_buttons.emplace_back(std::make_unique<ChooseLevel>(sf::Vector2f(width / 3 , height / 7),
    sf::Vector2f(width / 2 , 10 * height / 12), Action::LEVEL3));

  m_buttons.emplace_back(std::make_unique<Back>(sf::Vector2f(width / 7 , height / 15),
    sf::Vector2f(width / 10 , height / 12)));
}
