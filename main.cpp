#include "exceptions.h"
#include "game.h"
#include "gameover.h"
#include "menu.h"
#include <chrono>
#include <memory> //asa am reparat 6 erori de asan check si wondows gnu, luati aminte copii
#include "stateptr.h"

void startGame(sf::RenderWindow &window) {
  StatePtr currentState(new Game(window));

  while (window.isOpen()) {
    currentState->run();

    if (dynamic_cast<Game *>(currentState.get())->isGameOver()) {
      currentState = StatePtr(new GameOver(window));
      currentState->run();
      break;
    }
  }
}

int main() {
  sf::RenderWindow mainWindow(sf::VideoMode(1920, 1080), "Setris Game");

  try {
    Menu gameMenu(mainWindow); // pornim meniul

    while (mainWindow.isOpen()) {
      sf::Event event;
      while (mainWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
          mainWindow.close();
        else if (event.type == sf::Event::MouseButtonReleased) {
          if (event.mouseButton.button == sf::Mouse::Left) {
            if (gameMenu.playButtonClicked()) {
              gameMenu.close();      // inchidem meniul
              startGame(mainWindow); // deschidem functia cu care avem si jocul
                                     // si pierderea jocului (desi e cam greu sa
                                     // pierzi momentan (mai putin daca modific
                                     // sa mai pun o culoare)
            }
          }
        }
      }
      mainWindow.clear();
      gameMenu.run(); // desenam ce ne trb
      mainWindow.display();
    }

  }
  catch (const FailedToLoadResourceException &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  catch (const OutOfBoundsException &e) {
    std::cerr << e.what() << std::endl;
    return 2;
  }
  catch (const TetrisException &e) {
    std::cerr << e.what() << std::endl;
    return 3;
  }
  catch (...) {
    std::cerr << "Unknown exception" << std::endl;
    return 4;
  }

  return 0;
}