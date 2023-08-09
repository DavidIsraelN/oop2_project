#include "Buttons/Help.h"
#include "Buttons/Back.h"
#include "ResourcesManager.h"

//----------------------------------------------------------
Help::Help(float width, float height, const sf::Vector2f& size,
  const sf::Vector2f& position, const sf::Vector2f& window_size)
  : Button(size, position, "HELP"/*, Action::HELP*/),
  m_back(std::make_unique<Back>(sf::Vector2f(width / 10 , height / 15),
    sf::Vector2f(width / 13 , height / 12))),
  m_help(ResourceManager::Resource().getTexture(TextureIndex::HELP))
{
  m_help.setScale(window_size.x / m_help.getGlobalBounds().width,
    window_size.y / m_help.getGlobalBounds().height);
}

//----------------------------------------------------------
void Help::drawHelp(sf::RenderWindow& window) const
{
  window.draw(m_help);
  m_back->draw(window);
}

//----------------------------------------------------------
Action Help::action(sf::RenderWindow& window)
{
  window.clear();
  drawHelp(window);
  window.display();

  while (window.isOpen())
  {
    if (auto event = sf::Event{}; window.waitEvent(event))
      switch (event.type)
      {
      case sf::Event::Closed:
        window.close();
        break;

      case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::Escape)
          return m_back->action(window);
      
      case sf::Event::MouseButtonReleased:
        auto loc = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
        if (m_back->clickMe(loc))
          return m_back->action(window);
      }
  }
  return getAction(); // never got here.
}
