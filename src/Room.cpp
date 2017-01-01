#include "Room.h"
#include "Utils.h"
#include "Settings.h"

namespace GUI {
static const std::string ITEMS_STR = " items";
static const std::string POWER_STR = "W";
static const std::string CURRENCY_STR = "$";

Room::Room(sf::Sprite sprite, sf::Sprite exit_icon, std::string& name) : m_sprite(sprite), m_exit_sprite(exit_icon) {
  auto bounds = m_sprite.getGlobalBounds();
  auto color = sf::Color::Red;

  sf::Text text;
  utils::Utils::prepareText(text, name, 32, ResourceHolder::getInstance().getFont(), color);
  m_text_name = model::EditableTextLabelFactory::createEditableTextLabel(text);
  m_text_name->activate();
  m_text_name->setPosition(bounds.width / 2.f, bounds.height / 2.f);

  utils::Utils::prepareText(m_text_items_count, std::string(std::to_string(m_items.size()) + ITEMS_STR), 24, ResourceHolder::getInstance().getFont(), color);
  m_text_items_count.setPosition(bounds.width - m_text_items_count.getGlobalBounds().width / 2.f - 30, 36);

  utils::Utils::prepareText(m_text_power, std::string(utils::Utils::to_string(getTotalPower()) + POWER_STR), 24, ResourceHolder::getInstance().getFont(), color);
  m_text_power.setPosition(bounds.width  - m_text_power.getGlobalBounds().width / 2.f - 30, 72);

  utils::Utils::prepareText(m_text_cost, std::string(utils::Utils::to_string(getTotalCost()) + CURRENCY_STR), 24, ResourceHolder::getInstance().getFont(), color);
  m_text_cost.setPosition(bounds.width - m_text_cost.getGlobalBounds().width / 2.f - 30, 108);
}

Room::~Room() {

}

bool Room::isSelectable() const {
  return true;
}

void Room::select() {
  Component::select();
}

void Room::deselect() {
  Component::select();
}

void Room::activate() {

}

void Room::deactivate() {
}


void Room::handleEvent(const sf::Event& event) {

}

void Room::setPosition(float x , float y) {
  itemChanged();
  Component::setPosition(x, y);
}

void Room::move(float x, float y) {
  Component::move(x, y);
  m_text_name->move(x, y);
  m_exit_sprite.move(x, y);
  itemChanged();
}

void Room::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();
  target.draw(m_sprite, states);
  target.draw(m_text_items_count, states);
  target.draw(m_text_power, states);
  target.draw(m_text_cost, states);

  // Those are draw without parent transformation due to onClickEvents
  target.draw(m_exit_sprite);
  m_text_name->draw(target);

}

void Room::drawItems(sf::RenderTarget& target, sf::RenderStates states) const {
  if (!m_items.empty()) {
    for (auto item : m_items) {
      target.draw(*(item.get()), states);
    }
  }
}

void Room::drawItemInfo(sf::RenderTarget& target, sf::RenderStates states) const {
  sf::RectangleShape background;
  sf::Color gray (220, 220, 220);
  background.setFillColor(gray);
  background.setSize(sf::Vector2f(577.f, 537.f));
  background.setPosition(1042.f, 3.f);
  background.setOutlineColor(sf::Color::Black);
  background.setOutlineThickness(3.0f);

  target.draw(background);

  if (m_current_item != nullptr) {
    auto text = m_current_item->getItemName();
    text.setPosition(background.getGlobalBounds().left + background.getGlobalBounds().width / 2.f, 36.0f);
    target.draw(text, states);
    m_current_item->drawInfo(target, states, background);
  }
}

void Room::update() {
  if (!m_items.empty()) {
    for (auto item : m_items) {
      item->update();
    }
  }
  itemChanged();
}

void Room::setActiveItem(std::shared_ptr<RoomViewItem> item) {
  m_current_item = item;
}

void Room::appendItem(std::shared_ptr<RoomViewItem> roomviewitem) {
  m_items.push_back(roomviewitem);
  itemChanged();
}

sf::FloatRect Room::getGlobalBounds() {
  sf::Vector2f size(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height);
  auto position = const_cast<sf::Vector2f&>(getPosition());
  position.x += settings::LISTVIEW_WIDTH;
  return sf::FloatRect(position, size);
}

std::vector<std::shared_ptr<RoomViewItem>>& Room::getItems() {
  return m_items;
}

double Room::getTotalEnergy() {
  double energy = 0.0;
  if (!m_items.empty()) {
    for (auto item : m_items) {
      energy += item->getDevice().getEnergy();
    }
  }
  return energy;
}

double Room::getTotalCost() {
  double cost = 0.0;
  if (!m_items.empty()) {
    for (auto item : m_items) {
      cost += item->getDevice().getEnergyCost();
    }
  }
  return cost;
}

double Room::getTotalPower() {
  double power = 0.0;
  if (!m_items.empty()) {
    for (auto item : m_items) {
      power += item->getDevice().getPower();
    }
  }
  return power;
}

void Room::itemChanged() {
  auto bounds = m_sprite.getGlobalBounds();

  m_text_items_count.setString(std::string(std::to_string(m_items.size()) + ITEMS_STR));
  m_text_items_count.setPosition(bounds.width - m_text_items_count.getGlobalBounds().width / 2.f - settings::ROOM_ITEM_PROPERTIES_OFFSET, 36);

  m_text_power.setString(std::string(utils::Utils::to_string(getTotalPower()).append(POWER_STR)));
  m_text_power.setPosition(bounds.width  - m_text_power.getGlobalBounds().width / 2.f - settings::ROOM_ITEM_PROPERTIES_OFFSET, 72);

  m_text_cost.setString(std::string(utils::Utils::to_string(getTotalCost()).append(CURRENCY_STR)));
  m_text_cost.setPosition(bounds.width - m_text_cost.getGlobalBounds().width / 2.f - settings::ROOM_ITEM_PROPERTIES_OFFSET, 108);

}

sf::FloatRect Room::getGlobalBoundsOfExitIcon() {
  auto bounds = m_exit_sprite.getGlobalBounds();
  bounds.left += settings::LISTVIEW_WIDTH;
  return bounds;
}

void Room::removeRoomViewItem(std::vector<std::shared_ptr<RoomViewItem>>::iterator itr) {
  auto itr_cpy = itr;
  for ( ; itr != m_items.end(); ++itr) {
    (*itr)->move(0.0f, -1 * (*itr)->getGlobalBounds().height);
  }

  if (itr_cpy != m_items.end()) {
    if (*itr_cpy == m_current_item && itr == m_items.begin()) {
      changeItem(nullptr);
    } else changeItem(*(itr - 1));
    m_items.erase(itr_cpy);
  }
  itemChanged();
}

void Room::changeItem(std::shared_ptr<RoomViewItem> item) {
  m_current_item = item;
  if (item != nullptr) {
    setActiveItem(item);
  }
}
} /* namespace model */
