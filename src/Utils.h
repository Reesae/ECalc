#ifndef UTILS_H_
#define UTILS_H_
#include <SFML/Graphics/Text.hpp>

namespace utils {

class Utils {
  public:
    static void prepareText(sf::Text& text, const std::string& string, int size, sf::Font& font, sf::Color& color);
    static sf::Vector2f& scaleVecToView(sf::Vector2f& vector);
    static std::string to_string(double number, int precision = 2);
};

} /* namespace utils */

#endif /* UTILS_H_ */
