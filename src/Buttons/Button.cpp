#include "Buttons/Button.h"
#include "ResourcesManager.h"

Button::Button(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& text)
  : m_text(sf::Text(text, ResourceManager::Resource().getFont(FontIndex::TRY), size.y / 2))
{
  m_rectangle.setSize(size);
  m_rectangle.setPosition(position);
  m_rectangle.setOrigin(sf::Vector2f(m_rectangle.getGlobalBounds().width / 2, m_rectangle.getGlobalBounds().height / 2));
  m_rectangle.setFillColor(sf::Color(0, 0, 255, 100));
  m_text.setPosition(m_rectangle.getPosition());
  m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_rectangle.getOrigin().y / 1.5f);
  m_text.setFillColor(sf::Color::Cyan);
}



void Button::draw(sf::RenderWindow& window) const
{
  window.draw(m_rectangle);
  window.draw(m_text);
}

bool Button::clickMe(const sf::Vector2f& loc) const
{
  return m_rectangle.getGlobalBounds().contains(loc);
}