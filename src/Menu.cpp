#include "Menu.h"
#include "Buttons/Back.h"
#include "Buttons/Exit.h"
#include "Buttons/Help.h"
#include "Buttons/Mute.h"
#include "Buttons/NewGame.h"
#include "Buttons/Records.h"
#include "ResourcesManager.h"

//-------------------------------------------------------------------
Menu::Menu(float win_width, float win_height) :
  m_text_title(sf::Text("MENU", ResourceManager::Resource().getFont(), win_height / 5))
{
  buildMenu(win_width, win_height);
}

//-------------------------------------------------------------------
void Menu::buildMenu(float width, float height)
{
  m_text_title.setFillColor(sf::Color::Black);
  m_text_title.setPosition(width / 2, height / 4);
  m_text_title.setOrigin(m_text_title.getGlobalBounds().width / 2,
                         m_text_title.getGlobalBounds().height / 2);
  m_text_title.setStyle(sf::Text::Underlined);

  m_buttons.emplace_back(std::make_unique<Back>(sf::Vector2f(width / 10, height / 15),
    sf::Vector2f(width / 10 , height / 12), Action::BACK_TO_GAME));

  m_buttons.emplace_back(std::make_unique<Mute>(sf::Vector2f(width / 10, height / 15),
    sf::Vector2f(width - width / 10, height / 12), Action::BACK_TO_MENU));

  m_buttons.emplace_back(std::make_unique<NewGame>(width, height,
    sf::Vector2f(width / 3, height / 7), sf::Vector2f(2 * width / 7, 7 * height / 12)));

  m_buttons.emplace_back(std::make_unique<Help>(width, height, 
    sf::Vector2f(width / 3, height / 7), sf::Vector2f(5 * width / 7, 7 * height / 12),
    sf::Vector2f(width, height)));

  m_buttons.emplace_back(std::make_unique<Records>(width, height,
    sf::Vector2f(width / 3, height / 7), sf::Vector2f(5 * width / 7, 9.5 * height / 12)));

  m_buttons.emplace_back(std::make_unique<Exit>(
    sf::Vector2f(width / 3, height / 7), sf::Vector2f(2 * width / 7, 9.5 * height / 12)));
}

//-------------------------------------------------------------------
void Menu::drawMenu(sf::RenderWindow& window) const
{
  window.clear(sf::Color::Cyan);
  window.draw(m_text_title);
  for (auto i = size_t(m_back_button ? 0 : 1); i < m_buttons.size(); ++i)
    m_buttons[i]->draw(window);
  window.display();
}

//-------------------------------------------------------------------
Action Menu::run(sf::RenderWindow& window)
{
  while (window.isOpen())
  {
    drawMenu(window);

    if (auto event = sf::Event{}; window.waitEvent(event))
      switch (event.type)
      {
      case sf::Event::Closed:
        window.close();
        break;

      case sf::Event::MouseButtonReleased:
        Action action;
        auto loc = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
        for (auto i = size_t(m_back_button ? 0 : 1); i < m_buttons.size(); ++i)
          if (m_buttons[i]->clickMe(loc))
          {
            action = m_buttons[i]->action(window);
            if (action != Action::BACK_TO_MENU)
            {
              setBackButton(true);
              return action;
            }
          }
      }
  }
  return Action::MENU;
}

//-------------------------------------------------------------------
void Menu::setBackButton(bool back)
{
  m_back_button = back;
}
