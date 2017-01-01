#ifndef EDITABLETEXTLABEL_H_
#define EDITABLETEXTLABEL_H_

#include <SFML/Graphics.hpp>

namespace GUI {

enum VIEW_ENUM{ROOMVIEW, STATVIEW};

class EditableTextLabel {
  public:
    EditableTextLabel(sf::Text text, size_t max_length = DEFAULT_STRING_LENGTH);
    bool contains(sf::Vector2f cursor, VIEW_ENUM view = ROOMVIEW);
    void changeState();
    bool isActive();
    std::string getString();
    sf::FloatRect getLocalBounds();
    void setString(const std::string& string);
    void setPosition(float x, float y);
    void move(float x, float y);
    void draw(sf::RenderTarget& target) const;
    size_t getMaxLength();
    sf::Text getTextCopy();
    void activate();
    bool isSelectable();
    void deactivate();
  private:
    sf::Text m_text;
    bool m_active;
    size_t m_max_length;
    bool m_selectable;
    static constexpr size_t DEFAULT_STRING_LENGTH = 10;
};

} /* namespace GUI */

#endif /* EDITABLETEXTLABEL_H_ */
