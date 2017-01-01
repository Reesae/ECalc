#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include "ListViewImpl.h"
#include "GUIManager.h"
#include "EventHandler.h"
#include "Settings.h"
#include <iostream>
#include <functional>

int main() {
  sf::RenderWindow window(sf::VideoMode(settings::VIDEO_WIDTH, settings::VIDEO_HEIGHT), "EECalc", sf::Style::Fullscreen);
  window.setFramerateLimit(settings::FRAME_LIMIT);
  sf::RenderStates states;
  GUI::GUIManager gui(window);
  core::EventHandler eventhandler(window, gui);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
          window.close();
      } else if (event.type == sf::Event::MouseButtonPressed) {
        eventhandler.onMouseClicked(event);
      } else if (event.type == sf::Event::MouseWheelScrolled) {
        eventhandler.onMouseScrolled(event);
      } else if (event.type == sf::Event::TextEntered || event.type == sf::Event::KeyPressed) {
        eventhandler.onTextEntered(event);
      }
    }
    eventhandler.globalEvents();

    window.clear(sf::Color::White);
    gui.draw(states);

    window.display();
  }

  return 0;
}
