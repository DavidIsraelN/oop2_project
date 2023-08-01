#include "GameOver.h"
#include "Buttons/Exit.h"
#include "Buttons/MenuButton.h"
#include "ResourcesManager.h"
#include "EnumClassAction.h"


GameOver::GameOver(float win_width, float win_height, float info_height) :
         // m_rooms_rec({win_width, win_height}),
         m_game_over_txt("Game Over", ResourceManager::Resource().getFont(FontIndex::TRY), win_width / 14)
{
 // m_rooms_rec.setFillColor(semi_transparent);
  m_game_over_txt.setFillColor(sf::Color::White);
  m_game_over_txt.setOutlineThickness(10);
  //m_rooms_txt.setStyle(2);
  m_game_over_txt.setOutlineColor(sf::Color::Black);
  m_game_over_txt.setPosition({win_width / 2, win_height / 3});
  m_game_over_txt.setOrigin({m_game_over_txt.getGlobalBounds().width / 2,
                             m_game_over_txt.getGlobalBounds().height / 2});

  m_buttons.emplace_back(std::make_unique<Exit>(win_width, win_height));
  m_buttons.emplace_back(std::make_unique<MenuButton>(win_width, win_height));

}

void GameOver::draw(sf::RenderWindow& window) const
{
  window.draw(m_game_over_txt);
  std::for_each(m_buttons.begin(), m_buttons.end(), [&window](auto& button) {button->draw(window);});
}

Action GameOver::run(sf::RenderWindow& window) const
{
  while (window.isOpen())
  {
    window.clear(sf::Color::Cyan);
    draw(window);
    window.display();

    if (auto event = sf::Event{}; window.waitEvent(event))
      switch (event.type)
      {
      case sf::Event::Closed:
        window.close();
        return Action::EXIT;

      case sf::Event::MouseButtonReleased:
        auto loc = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
        for (auto &button : m_buttons)
          if (button->clickMe(loc)) return button->action(window);
      }
  }
  return Action::NOTHING;
}