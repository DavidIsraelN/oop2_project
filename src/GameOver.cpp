#include "GameOver.h"
#include "Buttons/Exit.h"
#include "Buttons/MenuButton.h"
#include "EnumAndMacroes.h"
#include "ResourcesManager.h"
#include <sstream>
#include <cctype>

//-------------------------------------------------------------------
GameOver::GameOver(float win_width, float win_height) :
  m_game_over_txt("Game Over", ResourceManager::Resource().getFont(FontIndex::TRY), win_width / 7),
  m_name_msg("Congratulations, achieving new record.\n\t\tInsert  name:",
    ResourceManager::Resource().getFont(FontIndex::TRY), win_width / 20),
  m_name("", ResourceManager::Resource().getFont(FontIndex::TRY), win_width / 20),
  m_file_records(ResourceManager::Resource().getTxtFile(TxtIndex::RECORD))
{
  buildGameOver(win_width, win_height);
}

//-------------------------------------------------------------------
void GameOver::buildGameOver(float width, float height)
{
  m_game_over_txt.setFillColor(sf::Color::White);
  m_game_over_txt.setOutlineThickness(10);
  m_game_over_txt.setOutlineColor(sf::Color::Black);
  m_game_over_txt.setPosition({ width / 2, height / 6 });
  m_game_over_txt.setOrigin({ m_game_over_txt.getGlobalBounds().width / 2,
                              m_game_over_txt.getGlobalBounds().height / 2 });

  m_name_msg.setFillColor(sf::Color::Blue);
  m_name_msg.setPosition(width / 2, height / 1.8);
  m_name_msg.setOrigin({ m_name_msg.getGlobalBounds().width / 2,
                         m_name_msg.getGlobalBounds().height / 2 });

  m_name.setFillColor(sf::Color::Blue);
  m_name.setPosition(width / 2.1, height / 1.77);

  m_buttons.emplace_back(std::make_unique<MenuButton>(
    sf::Vector2f(width / 3.f, height / 7.f), sf::Vector2f(2 * width / 7, 9.5f * height / 12)));

  m_buttons.emplace_back(std::make_unique<Exit>(
    sf::Vector2f(width / 3.f, height / 7.f), sf::Vector2f(5 * width / 7, 9.5f * height / 12)));
}

//-------------------------------------------------------------------
Action GameOver::run(sf::RenderWindow& window, size_t final_score)
{
  checkIfNewRecord(final_score);
  auto batton_pressed = Action::NOTHING;

  while (window.isOpen() && batton_pressed == Action::NOTHING)
  {
    drawGameOver(window, final_score);

    if (auto event = sf::Event{}; window.waitEvent(event))
      switch (event.type)
      {
      case sf::Event::Closed:
        window.close();
      break;

      case sf::Event::MouseButtonReleased: {
        auto loc = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
        for (auto& button : m_buttons)
          if (button->clickMe(loc)) batton_pressed = button->action(window);
      break; }
      
      case sf::Event::TextEntered:
        if (!m_new_record) break;
        setName(event.text.unicode, final_score);
      }
  }
  if (m_new_record) saveNewRecord(final_score);
  return batton_pressed;
}

//-------------------------------------------------------------------
void GameOver::checkIfNewRecord(size_t final_score)
{
  getSmallRecord();
  if (final_score > m_small_score) m_new_record = true;
}

//-------------------------------------------------------------------
void GameOver::getSmallRecord()
{
  backToStart();
  std::string line, name;
  size_t score, i;

  for (i = 0; i < MAX_NUM_OF_RECORDS; ++i)
  {
    if (m_file_records.eof()) break;

    std::getline(m_file_records, line);
    if (line == "" || line == "\n") break; // last line

    auto one_record = std::istringstream(line);
    one_record.exceptions(std::ios::failbit | std::ios::badbit);
    one_record >> name >> score;

    if (i == 0) m_small_score = score;
    if (score < m_small_score) m_small_score = score;
  }
  if (i < MAX_NUM_OF_RECORDS) m_small_score = 0;
}

//-------------------------------------------------------------------
void GameOver::drawGameOver(sf::RenderWindow& window, size_t final_score)
{
  auto score_msg = sf::Text("your score is: " + std::to_string(final_score),
    ResourceManager::Resource().getFont(FontIndex::TRY), window.getSize().x / 13);
  score_msg.setPosition(window.getSize().x / 2, window.getSize().y / 2.7);
  score_msg.setOrigin(score_msg.getGlobalBounds().width / 2, score_msg.getGlobalBounds().height / 2);
  score_msg.setFillColor(sf::Color::Black);

  m_name.setString(m_player_name);

  window.clear(sf::Color::Cyan);
  window.draw(m_game_over_txt);
  window.draw(score_msg);
  if (m_new_record) { window.draw(m_name_msg); window.draw(m_name); }
  std::for_each(m_buttons.begin(), m_buttons.end(), [&window](auto& button) {button->draw(window);});
  window.display();
}

//-------------------------------------------------------------------
void GameOver::setName(sf::Uint32 c, size_t final_score)
{
  if (c == 8 && !m_player_name.empty())  // if delete the last char
    m_player_name.pop_back();

  else if (c == 13)                      // if enter is entered 
    saveNewRecord(final_score);

  else if (m_player_name.size() >= MAX_PLAYER_NAME)
    return;

  else if (std::isalnum(c) || c == '.')  // valid character for player name
    m_player_name += char(c);
}

//-------------------------------------------------------------------
void GameOver::saveNewRecord(size_t final_score)
{
  if (m_file_records.fail()) m_file_records.clear();

  if (m_player_name.empty())   // name not entered.
    m_player_name = "new.record";

  if (m_player_name.size() < MAX_PLAYER_NAME)  // fill name with spaces
    for (auto i = m_player_name.size(); i < MAX_PLAYER_NAME; ++i) m_player_name += ' ';

  if (m_small_score == 0)   // num of records in the file < MAX_NUM_OF_RECORDS.
    m_file_records.seekp(0, m_file_records.end); // go to the end of the file.

  else {                    // need to replase the small record which exist in file.
    backToStart();
    std::string line, name;
    size_t score, i;
    for (i = 0; i < MAX_NUM_OF_RECORDS; ++i)
    {
      if (m_file_records.eof()) break; // not supposed to get here

      std::getline(m_file_records, line);
      auto one_record = std::istringstream(line);
      one_record.exceptions(std::ios::failbit | std::ios::badbit);
      one_record >> name >> score;
      if (score == m_small_score) break;
    }

    std::streampos start_of_line = m_file_records.tellg() - std::streampos(line.size() + 2);
    m_file_records.seekp(start_of_line);
    //for (i = 0; i < line.size(); ++i) m_file_records.put(' '); 
    //m_file_records.seekp(start_of_line);
  }

  // here the writing marker is necessarily in the first character
  // of the line where the new data should be inserted

  size_t i = MAX_SCORE_DIGIT, j; // length of max score digits
  for (j = final_score; i > 0 && j > 0 ; --i, j /= 10) { }
  m_file_records << m_player_name << ' ' << final_score;
  for (; i > 0; --i) m_file_records << ' ';
  m_file_records << "\n";

  m_new_record = false;
  m_player_name = "";
}

//-------------------------------------------------------------------
void GameOver::backToStart()
{
  if (m_file_records.fail()) m_file_records.clear();
  m_file_records.seekg(0, m_file_records.beg);
}
