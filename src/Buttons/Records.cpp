#include "Buttons/Records.h"
#include "Buttons/Back.h"
#include "EnumClassAction.h"
#include "ResourcesManager.h"
#include "Colors.h"
#include <sstream>

//----------------------------------------------------------
Records::Records(float width, float height, const sf::Vector2f& size, const sf::Vector2f& position)
  : Button(size, position, "RECORDS"),
  m_back(std::make_unique<Back>(sf::Vector2f(width / 7, height / 15),
    sf::Vector2f(width / 10, height / 12))),
  m_txt_title(sf::Text("RECORDS",
      ResourceManager::Resource().getFont(FontIndex::TRY), height / 6)),
  m_file_records(ResourceManager::Resource().getTxtFile(TxtIndex::RECORD))
{
  m_txt_title.setFillColor(sf::Color::Black);
  m_txt_title.setPosition(width / 2, height / 5);
  m_txt_title.setOrigin(m_txt_title.getGlobalBounds().width / 2,
    m_txt_title.getGlobalBounds().height / 2);
  m_txt_title.setStyle(sf::Text::Underlined);
}

//----------------------------------------------------------
Action Records::action(sf::RenderWindow& window)
{
  loadRecords(window);

  window.clear(main_beckground);
  drawRecords(window);
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
  window.draw(m_txt_title);
  window.draw(m_txt_records);
}

//----------------------------------------------------------
void Records::loadRecords(sf::RenderWindow& window)
{
  backToStart();
  m_records.clear();

  std::string line, name, records = "";
  auto space = std::string("\t..................\t");
  size_t score;
  
  for (auto i = size_t(0); i < MAX_NUM_OF_RECORDS; ++i)
  {
    if (m_file_records.eof()) break;

    std::getline(m_file_records, line);
    auto one_record = std::istringstream(line);
    one_record.exceptions(std::ios::failbit | std::ios::badbit);
    one_record >> name >> score;
    m_records.emplace(score, name);
  }

  std::for_each(m_records.rbegin(), m_records.rend(), [&records, &space](auto& rec) {
    records += (rec.second + space + std::to_string(rec.first) + "\n"); });

  m_txt_records.setString(records);
  m_txt_records.setFont(ResourceManager::Resource().getFont(FontIndex::TRY));
  m_txt_records.setCharacterSize(window.getSize().y / 17);
  m_txt_records.setFillColor(sf::Color::Blue);
  m_txt_records.setPosition(window.getSize().x / 2, window.getSize().y / 1.5);
  m_txt_records.setOrigin(m_txt_records.getGlobalBounds().width / 2, 
    m_txt_records.getGlobalBounds().height / 2);
}

//-------------------------------------------------------------------
void Records::backToStart()
{
  m_file_records.seekg(0, m_file_records.beg);
}
