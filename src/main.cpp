#include "Controller.h"

int main()
{
  Controller().run();
  return EXIT_SUCCESS;
}


//
//#include <SFML/Graphics.hpp>
//
//int main()
//{
//  sf::RenderWindow window(sf::VideoMode(800, 600), "Ball Jump");
//
//  // Load the ball texture
//  sf::Texture ballTexture;
//  if (!ballTexture.loadFromFile("RedBall.png"))
//  {
//    // Handle error if the texture fails to load
//    return -1;
//  }
//
//  // Create the ball sprite
//  sf::Sprite ball(ballTexture);
//  ball.setPosition(400, 300);
//
//  // Set initial velocities and gravity
//  float initialVelocityY = -0.1f;
//  float velocityY = initialVelocityY;
//  const float gravity = 0.001f;
//  float velocityX = 0.1f; // Horizontal velocity
//
//  while (window.isOpen())
//  {
//    sf::Event event;
//    while (window.pollEvent(event))
//    {
//      if (event.type == sf::Event::Closed)
//      {
//        window.close();
//      }
//    }
//
//    // Update the position and velocity of the ball
//    ball.move(velocityX, velocityY);
//    velocityY += gravity;
//
//    // Check if the ball reaches the bottom of the window
//    if (ball.getPosition().y + ball.getGlobalBounds().height > window.getSize().y)
//    {
//      // Reverse the velocity to make the ball jump up
//      velocityY = -velocityY;
//    }
//
//    // Check if the ball reaches the window boundaries
//    if (ball.getPosition().x < 0 || ball.getPosition().x + ball.getGlobalBounds().width > window.getSize().x)
//    {
//      // Reverse the horizontal velocity to change direction
//      velocityX = -velocityX;
//    }
//
//    window.clear();
//    window.draw(ball);
//    window.display();
//  }
//
//  return 0;
//}
//
//#include <SFML/Graphics.hpp>
//
//int main()
//{
//  sf::RenderWindow window(sf::VideoMode(800, 600), "Ball Jump");
//
//  // Load the ball texture
//  sf::Texture ballTexture;
//  if (!ballTexture.loadFromFile("RedBall.png"))
//  {
//    // Handle error if the texture fails to load
//    return -1;
//  }
//
//  // Create the ball sprite
//  sf::Sprite ball(ballTexture);
//  ball.setPosition(400, 300);
//
//  // Set initial velocities and gravity
//  float initialVelocityY = -0.05f;
//  float velocityY = initialVelocityY;
//  float velocityX = 0.05f; // Horizontal velocity
//  const float gravity = 0.005f;
//
//  while (window.isOpen())
//  {
//    sf::Event event;
//    while (window.pollEvent(event))
//    {
//      if (event.type == sf::Event::Closed)
//      {
//        window.close();
//      }
//    }
//
//    // Update the position and velocity of the ball
//    ball.move(velocityX, velocityY);
//    velocityY += gravity;
//
//    // Check if the ball reaches the bottom or top of the window
//    if (ball.getPosition().y + ball.getGlobalBounds().height > window.getSize().y)
//    {
//      // Reverse the vertical velocity to make the ball jump up
//      velocityY = -velocityY;
//    }
//    else if (ball.getPosition().y < 0)
//    {
//      // Reverse the vertical velocity to make the ball jump down
//      velocityY = -velocityY;
//    }
//
//    // Check if the ball reaches the left or right boundaries of the window
//    if (ball.getPosition().x + ball.getGlobalBounds().width > window.getSize().x)
//    {
//      // Reverse the horizontal velocity to change direction to the left
//      velocityX = -velocityX;
//    }
//    else if (ball.getPosition().x < 0)
//    {
//      // Reverse the horizontal velocity to change direction to the right
//      velocityX = -velocityX;
//    }
//
//    window.clear();
//    window.draw(ball);
//    window.display();
//  }
//
//  return 0;
//}










//#include <SFML/Graphics.hpp>
//
//int main()
//{
//  sf::RenderWindow window(sf::VideoMode(800, 600), "Ball Jump");
//
//  // Load the ball texture
//  sf::Texture ballTexture;
//  if (!ballTexture.loadFromFile("RedBall.png"))
//  {
//    // Handle error if the texture fails to load
//    return -1;
//  }
//
//  // Create the ball sprite
//  sf::Sprite ball(ballTexture);
//  ball.setPosition(400, 300);
//
//  // Set constant velocities
//  float velocityX = 0.2f; // Horizontal velocity
//  float velocityY = -0.2f; // Vertical velocity
//
//  while (window.isOpen())
//  {
//    sf::Event event;
//    while (window.pollEvent(event))
//    {
//      if (event.type == sf::Event::Closed)
//      {
//        window.close();
//      }
//    }
//
//    // Update the position of the ball using constant velocities
//    ball.move(velocityX, velocityY);
//
//    // Check if the ball reaches the boundaries of the window
//    if (ball.getPosition().x + ball.getGlobalBounds().width > window.getSize().x || ball.getPosition().x < 0)
//    {
//      // Reverse the horizontal velocity to change direction
//      velocityX = -velocityX;
//    }
//    if (ball.getPosition().y + ball.getGlobalBounds().height > window.getSize().y || ball.getPosition().y < 0)
//    {
//      // Reverse the vertical velocity to change direction
//      velocityY = -velocityY;
//    }
//
//    window.clear();
//    window.draw(ball);
//    window.display();
//  }
//
//  return 0;
//}
