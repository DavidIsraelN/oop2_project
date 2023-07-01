#include "Buttons/Help.h"
#include "EnumClassAction.h"
#include "ResourcesManager.h"

Help::Help(float width, float height)
    : Button(sf::Vector2f(width / 3.f, height / 7.f), sf::Vector2f(width / 2, 6.f * height / 12), "Help") { }


Action Help::action(sf::RenderWindow& window)
{
  window.clear();
  auto help = sf::Sprite(ResourceManager::Resource().getObjTexture(ObjIndex::RED_BALL));
  window.draw(help);
  window.display();
  while (window.isOpen())
  {
    if (auto event = sf::Event{}; window.waitEvent(event))
      switch (event.type)
      {
      case sf::Event::Closed:
        window.close();
        break;

//      case sf::Event::KeyPressed:
//        if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::B)
//          return false;

//      case sf::Event::MouseButtonReleased:
//        auto loc = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
//        if (m_back.clickMe(loc))
//          return m_back.action(window, level_m);
      }
  }
  return Action::HELP;
}
