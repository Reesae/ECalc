#include "EditableTextLabel.h"
#include "Utils.h"
#include "Settings.h"
namespace GUI {

EditableTextLabel::EditableTextLabel(sf::Text text, size_t max_length) : m_text(text), m_active(false),
    m_max_length(max_length), m_selectable(false) {

}

bool EditableTextLabel::contains(sf::Vector2f cursor, VIEW_ENUM view) {
  auto bounds = m_text.getGlobalBounds();
  if (view == ROOMVIEW) {
    bounds.left += settings::LISTVIEW_WIDTH;
  } else if (view == STATVIEW) {
    bounds.top += settings::STATVIEW_HEIGHT;
    bounds.left += settings::VIDEO_WIDTH - settings::STATVIEW_WIDTH;
  }
  return bounds.contains(cursor);
}

void EditableTextLabel::changeState() {
  m_active = !m_active;
}

bool EditableTextLabel::isActive() {
  return m_active;
}

std::string EditableTextLabel::getString() {
  return m_text.getString();
}

sf::FloatRect EditableTextLabel::getLocalBounds() {
  return m_text.getLocalBounds();
}


void EditableTextLabel::setString(const std::string& string) {
  m_text.setString(string);
}

void EditableTextLabel::setPosition(float x, float y) {
  m_text.setPosition(x, y);
}

void EditableTextLabel::move(float x, float y) {
  m_text.move(x ,y);
}

void EditableTextLabel::draw(sf::RenderTarget& target) const {
  target.draw(m_text);
}

size_t EditableTextLabel::getMaxLength() {
  return m_max_length;
}

sf::Text EditableTextLabel::getTextCopy() {
  return m_text;
}

void EditableTextLabel::activate() {
  m_selectable = true;
}

bool EditableTextLabel::isSelectable() {
  return m_selectable;
}

void EditableTextLabel::deactivate() {
  m_selectable = false;
}
} /* namespace GUI */
