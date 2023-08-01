#include "Buttons/NewGame.h"
#include "Buttons/ChooseLevel.h"
#include "Buttons/Back.h"
#include "EnumClassAction.h"
#include "ResourcesManager.h"

NewGame::NewGame(float width, float height)
  : m_text_title(sf::Text("Choose Level", ResourceManager::Resource().getFont(FontIndex::TRY) , height / 8)),
      Button(sf::Vector2f(width / 3.f, height / 7.f), sf::Vector2f(width / 2, 4 * height / 12), "New Game")
{
  m_text_title.setFillColor(sf::Color::Black);
  m_text_title.setPosition(width / 2, height / 10);
  m_text_title.setOrigin(m_text_title.getGlobalBounds().width / 2,
                         m_text_title.getGlobalBounds().height / 2);

  m_levels.emplace_back(std::make_unique<ChooseLevel>(sf::Vector2f({ width / 3.f , height / 7.f}), sf::Vector2f({ width / 2 , 4.5f * height / 12}), Action::LEVEL1));
  m_levels.emplace_back(std::make_unique<ChooseLevel>(sf::Vector2f({ width / 3.f , height / 7.f}), sf::Vector2f({ width / 2 , 7 * height / 12}), Action::LEVEL2));
  m_levels.emplace_back(std::make_unique<ChooseLevel>(sf::Vector2f({ width / 3.f , height / 7.f}), sf::Vector2f({ width / 2 , 9.5f * height / 12}), Action::LEVEL3));
  m_levels.emplace_back(std::make_unique<Back>(sf::Vector2f({ width / 10 , height / 15 }), sf::Vector2f({ width / 13 , 1 * height / 12}), Action::BACK));
}

Action NewGame::action(sf::RenderWindow& window)
{
  window.clear(sf::Color::Cyan);
  window.draw(m_text_title);
  for (auto i = size_t(0); i < m_levels.size(); ++i)
    m_levels[i]->draw(window);
  window.display();
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
        for (auto &level : m_levels)
          if (level->clickMe(loc)) return level->action(window);
      }
  }
  return Action::NOTHING;
}
