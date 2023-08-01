#include "Menu.h"
#include "Buttons/NewGame.h"
#include "Buttons/Help.h"
#include "Buttons/Exit.h"
#include "Buttons/Records.h"
#include "Buttons/Back.h"
#include "EnumClassAction.h"
#include "ResourcesManager.h"
#include <iostream>

Menu::Menu(float win_width, float win_height)
    : m_text_title(sf::Text("MENU", ResourceManager::Resource().getFont(FontIndex::TRY) , win_height / 8))
{
  m_text_title.setFillColor(sf::Color::Black);
  m_text_title.setPosition(win_width / 2, win_height / 10);
  m_text_title.setOrigin(m_text_title.getGlobalBounds().width / 2,
                         m_text_title.getGlobalBounds().height / 2);

//  m_buttons.push_back(std::make_unique<Back>(win_width, win_height));
  m_buttons.emplace_back(std::make_unique<Back>(sf::Vector2f({ win_width / 10 , win_height / 15 }),
    sf::Vector2f({ win_width / 13 , 1 * win_height / 12}), Action::BACK_TO_GAME));
  m_buttons.emplace_back(std::make_unique<NewGame>(win_width, win_height));
  m_buttons.emplace_back(std::make_unique<Help>(win_width, win_height));
  m_buttons.emplace_back(std::make_unique<Records>(win_width, win_height));
  m_buttons.emplace_back(std::make_unique<Exit>(win_width, win_height));
//  m_buttons.push_back(std::make_unique<ExitGame>(sf::Vector2f(width / 2, height / 1.3f), height / 15));
//  m_buttons.push_back(std::make_unique<Mute>(sf::Vector2f(width / 13, height / 25), height / 35));
}

void Menu::draw(sf::RenderWindow& window) const
{
  window.draw(m_text_title);
  for (auto i = size_t(m_back_button ? 0 : 1); i < m_buttons.size(); ++i)
    m_buttons[i]->draw(window);
}

Action Menu::run(sf::RenderWindow& window)
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
        break;

      case sf::Event::MouseButtonReleased:
        Action action;
        auto loc = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
        for (auto &button : m_buttons)
          if (button->clickMe(loc))
          {
            action = button->action(window);
            if (action != Action::BACK)
            {
              setBackButton(true);
              return action;
            }
          }
      }
  }
  return Action::MENU;
}

void Menu::setBackButton(bool back)
{
  m_back_button = back;
}