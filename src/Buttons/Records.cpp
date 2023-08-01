#include "Buttons/Records.h"
#include "Buttons/Back.h"
#include "EnumClassAction.h"
#include "ResourcesManager.h"
#include <fstream>

#include <iostream>

//----------------------------------------------------------
Records::Records(float width, float height, const sf::Vector2f& size, const sf::Vector2f& position)
  : Button(size, position, "Records"/*, Action::RECORDS*/),
  m_back(std::make_unique<Back>(sf::Vector2f({ width / 10 , height / 15 }),
    sf::Vector2f({ width / 13 , 1 * height / 12 }), Action::BACK_TO_MENU))
{
  loadRecords();
}

//----------------------------------------------------------
void Records::loadRecords()
{
  std::ifstream& inputFile(ResourceManager::Resource().getTxtFile(TxtIndex::RECORD));
  if (inputFile.is_open())
  {
    inputFile >> m_record;
    inputFile.close();
  }
  else
  {
    std::cout << "Unable to open file for reading!" << std::endl;
  }
  updateRecord(7);
}

//----------------------------------------------------------
Action Records::action(sf::RenderWindow& window)
{
  window.clear();
  draw(window);
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

//----------------------------------------------------------
void Records::drawRecords(sf::RenderWindow& window) const
{
  m_back->draw(window);
}

//----------------------------------------------------------
size_t Records::getRecord() const
{
  return m_record;
}

//----------------------------------------------------------
void Records::updateRecord(size_t new_record)
{
//  std::fstream& outputFile(ResourceManager::Resource().getTxtFile(TxtIndex::RECORD));
//  if (outputFile.is_open())
//  {
//    outputFile << new_record;
//    outputFile.close();
//    m_record = new_record;
//    std::cout << m_record << "\n";
//  }
//  else
//  {
//    std::cout << "Unable to open file for writing!" << std::endl;
//  }
}
