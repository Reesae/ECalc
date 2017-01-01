#include "Utils.h"
#include "Settings.h"
#include <cmath>
#include <iostream>
#include <iomanip>

namespace utils {

void Utils::prepareText(sf::Text& text, const std::string& string, int size, sf::Font& font, sf::Color& color) {
  text.setString(string);
  text.setFont(font);
  text.setCharacterSize(size);
  text.setFillColor(sf::Color::White);
  text.setOutlineColor(sf::Color::Black);
  text.setOutlineThickness(2.0f);

  text.setOrigin(text.getLocalBounds().left + round(text.getGlobalBounds().width / 2),
    text.getLocalBounds().top + round(text.getGlobalBounds().height / 2));
}

sf::Vector2f& Utils::scaleVecToView(sf::Vector2f& vector) {
  vector.x = vector.x / settings::VIDEO_WIDTH;
  vector.y = vector.y / settings::VIDEO_HEIGHT;
  return vector;
}

std::string Utils::to_string(double number, int precision) {
  std::stringstream ss;
  ss << std::fixed << std::setprecision(precision) << number;
  return ss.str();

}

} /* namespace utils */
