#include "Buttons/Records.h"
#include "EnumClassAction.h"
#include "ResourcesManager.h"
#include <iostream>
#include <fstream>

Records::Records(float width, float height)
    : Button(sf::Vector2f(width / 3.f, height / 7.f), sf::Vector2f(width / 2, 8.f * height / 12), "Records")
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


Action Records::action(sf::RenderWindow& window)
{
  return Action::RECORDS;
}

size_t Records::getRecord() const
{
  return m_record;
}

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