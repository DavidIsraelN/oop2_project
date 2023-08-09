#pragma once
#include "Buttons/Button.h"
#include <SFML/Graphics.hpp>

/* ------------------------------------------------------------------
 * This class is responsible for game over screen.
 * and set the score to Record file if needed.
 */

class GameOver
{
public:
  GameOver(float, float);
  Action run(sf::RenderWindow&, size_t);

private:
  void buildGameOver(float, float);
  void drawGameOver(sf::RenderWindow&, size_t);
  void checkIfNewRecord(size_t);
  void getSmallRecord();
  void setName(sf::Uint32, size_t);
  void saveNewRecord(size_t);
  void backToStart();

  std::fstream& m_file_records;
  std::string m_player_name = "";
  bool m_new_record = false;
  size_t m_small_score = 0;
  std::vector<std::unique_ptr<Button>> m_buttons;
  sf::Text m_game_over_txt, m_name_msg, m_score_msg, m_name;
};
