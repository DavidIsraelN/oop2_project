#include "Buttons/Help.h"
#include "Buttons/Back.h"
#include "EnumAndMacroes.h"
#include "ResourcesManager.h"

//----------------------------------------------------------
Help::Help(float width, float height, const sf::Vector2f& size, const sf::Vector2f& position)
  : Button(size, position, "HELP"/*, Action::HELP*/),
  m_back(std::make_unique<Back>(sf::Vector2f({ width / 10 , height / 15 }),
    sf::Vector2f({ width / 13 , 1 * height / 12 }), Action::BACK_TO_MENU))
{
  loadHelp();
}

//----------------------------------------------------------
void Help::loadHelp()
{

}

//----------------------------------------------------------
void Help::drawHelp(sf::RenderWindow& window) const
{
//  auto help = sf::Sprite(ResourceManager::Resource().getObjTexture(ObjIndex::BALL));
//  window.draw(help);
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




////-------------------------------------------------------------------
//void Help::readHelpTxt()
//{
//  std::string line;
//  m_help_str.clear();
//  while (std::getline(ResourceManager::Resource().getTxtFile(TxtIndex::HELP), line))
//    m_help_str.push_back(line);
//}
//
////-------------------------------------------------------------------
//void Help::buildHelpScreen()
//{
//  m_help_rect.setFillColor(SemiSoftYellow);
//  auto line_height = m_window_width / m_help_str.size();
//  for (auto i = size_t(0); i < m_help_str.size(); ++i)
//  {
//    if (m_help_str[i].empty())
//      continue;
//    auto line = sf::Text(m_help_str[i], ResourceManager::Resource().getFont(FontIndex::ARIEL),
//      (m_help_txt.size() == 0) ? line_height * 2 : line_height / 1.5);
//    line.setFillColor(DeepRed);
//    line.setPosition({ m_window_width / 2, line_height * i });
//    line.setOrigin(line.getLocalBounds().width / 2, line.getLocalBounds().height / 2);
//    m_help_txt.push_back(line);
//  }
//
//  if (m_help_txt.size() < 1) return;
//  m_help_txt[0].setFont(ResourceManager::Resource().getFont(FontIndex::PACMAN));
//  m_help_txt[0].setStyle(sf::Text::Underlined);
//}

//#include "Colors.h"
//#include <fstream>
//
////-------------------------------------------------------------------
//Help::Help(float width, float height) :
//  Button("Help", { width / 2 , height / 1.75f }, height / 15, SoftYellow),
//  m_back({ width - width / 13 , height / 25 }, height / 35),
//  m_help_rect({ width, height }),
//  m_window_width(width), m_window_height(height)
//{
//  readHelpTxt();
//  buildHelpScreen();
//}
//
////-------------------------------------------------------------------
//bool Help::action(sf::RenderWindow& window, LevelManager& level_m)
//{
//  drawHelp(window);
//  while (window.isOpen())
//  {
//    if (auto event = sf::Event{}; window.waitEvent(event))
//      switch (event.type)
//      {
//      case sf::Event::Closed:
//        window.close();
//        break;
//
//      case sf::Event::KeyPressed:
//        if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::B)
//          return false;
//
//      case sf::Event::MouseButtonReleased:
//        auto loc = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
//        if (m_back.clickMe(loc))
//          return m_back.action(window, level_m);
//      }
//  }
//  return false;
//}
//
////-------------------------------------------------------------------
//void Help::readHelpTxt()
//{
//  std::string line;
//  m_help_str.clear();
//  while (std::getline(ResourceManager::Resource().getTxtFile(TxtIndex::HELP), line))
//    m_help_str.push_back(line);
//}
//
////-------------------------------------------------------------------
//void Help::buildHelpScreen()
//{
//  m_help_rect.setFillColor(SemiSoftYellow);
//  auto line_height = m_window_width / m_help_str.size();
//  for (auto i = size_t(0); i < m_help_str.size(); ++i)
//  {
//    if (m_help_str[i].empty())
//      continue;
//    auto line = sf::Text(m_help_str[i], ResourceManager::Resource().getFont(FontIndex::ARIEL),
//      (m_help_txt.size() == 0) ? line_height * 2 : line_height / 1.5);
//    line.setFillColor(DeepRed);
//    line.setPosition({ m_window_width / 2, line_height * i });
//    line.setOrigin(line.getLocalBounds().width / 2, line.getLocalBounds().height / 2);
//    m_help_txt.push_back(line);
//  }
//
//  if (m_help_txt.size() < 1) return;
//  m_help_txt[0].setFont(ResourceManager::Resource().getFont(FontIndex::PACMAN));
//  m_help_txt[0].setStyle(sf::Text::Underlined);
//}
//
////-------------------------------------------------------------------
//void Help::drawHelp(sf::RenderWindow& window) const
//{
//  window.clear(DeepRed);
//  window.draw(m_help_rect);
//  m_back.draw(window);
//  for (auto i = size_t(0); i < m_help_txt.size(); ++i)
//    window.draw(m_help_txt[i]);
//  window.display();
//}
