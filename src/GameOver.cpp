#include "GameOver.h"
#include "Buttons/Exit.h"
#include "Buttons/MenuButton.h"
#include "ResourcesManager.h"
#include "EnumClassAction.h"

//----------------------------------------------------------
GameOver::GameOver(float win_width, float win_height) :
  m_game_over_txt("Game Over", ResourceManager::Resource().getFont(FontIndex::TRY), win_width / 7)
{
  buildGameOver(win_width, win_height);
}

//----------------------------------------------------------
void GameOver::buildGameOver(float width, float height)
{
  // m_rooms_rec.setFillColor(semi_transparent);
  m_game_over_txt.setFillColor(sf::Color::White);
  m_game_over_txt.setOutlineThickness(10);
  //m_rooms_txt.setStyle(2);
  m_game_over_txt.setOutlineColor(sf::Color::Black);
  m_game_over_txt.setPosition({ width / 2, height / 4 });
  m_game_over_txt.setOrigin({ m_game_over_txt.getGlobalBounds().width / 2,
                              m_game_over_txt.getGlobalBounds().height / 2 });

  m_buttons.emplace_back(std::make_unique<MenuButton>(
    sf::Vector2f(width / 3.f, height / 7.f), sf::Vector2f(2 * width / 7, 9.f * height / 12)));

  m_buttons.emplace_back(std::make_unique<Exit>(
    sf::Vector2f(width / 3.f, height / 7.f), sf::Vector2f(5 * width / 7, 9.f * height / 12)));
}

//----------------------------------------------------------
void GameOver::drawGameOver(sf::RenderWindow& window, size_t final_score) const
{
  auto score = sf::Text("your score is : " + std::to_string(final_score),
                        ResourceManager::Resource().getFont(FontIndex::TRY), window.getSize().x / 13);
  score.setPosition({ float(window.getSize().x) / 2, float(window.getSize().y) / 2 });
  score.setOrigin({ score.getGlobalBounds().width / 2, score.getGlobalBounds().height / 2 });
  score.setFillColor(sf::Color::Black);

  window.clear(sf::Color::Cyan);
  window.draw(m_game_over_txt);
  window.draw(score);
  std::for_each(m_buttons.begin(), m_buttons.end(), [&window](auto& button) {button->draw(window);});
  window.display();
}

//----------------------------------------------------------
Action GameOver::run(sf::RenderWindow& window, size_t final_score) const
{
  while (window.isOpen())
  {
    drawGameOver(window, final_score);

    if (auto event = sf::Event{}; window.waitEvent(event))
      switch (event.type)
      {
      case sf::Event::Closed:
        window.close();
        return Action::NOTHING;

      case sf::Event::MouseButtonReleased:
        auto loc = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
        for (auto &button : m_buttons)
          if (button->clickMe(loc)) return button->action(window);
      }
  }
  return Action::NOTHING;
}
