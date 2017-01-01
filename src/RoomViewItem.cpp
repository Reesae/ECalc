#include "RoomViewItem.h"
#include "Utils.h"
#include "Settings.h"

namespace GUI {
static const char * POWER_STRING_PREFIX       = "Power [W]:";
static const char * USAGE_TIME_STRING_PREFIX  = "Usage time:";
static const char * ENERGY_USED_STRING_PREFIX = "Energy used [kWh]:";
static const char * ENERGY_COST_STRING_PREFIX = "Energy cost [$]:";

RoomViewItem::RoomViewItem(sf::Sprite sprite, sf::Sprite icon, model::Device device)
  : m_sprite(sprite), m_exit_sprite(icon), m_device(device) {

  preparePrefixText();
  prepareText();
}

RoomViewItem::~RoomViewItem() {
}

bool RoomViewItem::isSelectable() const {
  return true;
}

void RoomViewItem::select() {
  Component::select();
}

void RoomViewItem::deselect() {
  Component::select();
}

void RoomViewItem::activate() {

}

void RoomViewItem::deactivate() {
}

void RoomViewItem::handleEvent(const sf::Event& event) {
}

void RoomViewItem::move(float x, float y) {
  Component::move(x, y);
  m_exit_sprite.move(x, y);
  m_text_name->move(x, y);
  m_sprite.move(x, y);
}

void RoomViewItem::setPosition(float x, float y) {
  Component::setPosition(x, y);
  m_exit_sprite.setPosition(x, y);
  m_text_name->setPosition(x, y);
  m_sprite.setPosition(x, y);
}

void RoomViewItem::setText(const std::string& text) {

}

void RoomViewItem::draw(sf::RenderTarget& target, sf::RenderStates states) const {

  states.transform *= getTransform();
  target.draw(m_sprite);
  target.draw(m_text_name->getTextCopy());
  target.draw(m_exit_sprite);
  m_text_name->activate();
}

sf::FloatRect RoomViewItem::getGlobalBounds() {
  sf::Vector2f size(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height);
  auto position = const_cast<sf::Vector2f&>(getPosition());
  position.x += settings::LISTVIEW_WIDTH;
  return sf::FloatRect(position, size);
}

model::Device& RoomViewItem::getDevice() {
  return m_device;
}

void RoomViewItem::prepareText() {
  sf::FloatRect bounds = m_sprite.getGlobalBounds();
  auto color = sf::Color::Blue;
  sf::Text text;
  utils::Utils::prepareText(text, m_device.getName(), 32,
    ResourceHolder::getInstance().getFont(), color);
  m_text_name = model::EditableTextLabelFactory::createEditableTextLabel(text, 16);

  utils::Utils::prepareText(text, utils::Utils::to_string(m_device.getPower()), 32,
    ResourceHolder::getInstance().getFont(), color);
  m_text_power = model::EditableTextLabelFactory::createEditableTextLabel(text);
  m_text_power->activate();

  utils::Utils::prepareText(text, m_device.getUsageTimeAsString(), 32,
    ResourceHolder::getInstance().getFont(), color);
  m_text_time = model::EditableTextLabelFactory::createEditableTextLabel(text, 5);
  m_text_time->activate();
  utils::Utils::prepareText(m_text_energy_used, utils::Utils::to_string(m_device.getEnergyInKwh()), 32,
    ResourceHolder::getInstance().getFont(), color);

  utils::Utils::prepareText(m_text_energy_cost, utils::Utils::to_string(m_device.getEnergyCost()), 32,
    ResourceHolder::getInstance().getFont(), color);
  m_text_name->setPosition(bounds.width / 2.f, bounds.height / 2.f);
}

void RoomViewItem::preparePrefixText() {
  auto color = sf::Color::Blue;
  utils::Utils::prepareText(m_power_prefix, POWER_STRING_PREFIX, 32,
      ResourceHolder::getInstance().getFont(), color);
  utils::Utils::prepareText(m_usage_time_prefix, USAGE_TIME_STRING_PREFIX, 32,
      ResourceHolder::getInstance().getFont(), color);
  utils::Utils::prepareText(m_energy_used_prefix, ENERGY_USED_STRING_PREFIX, 32,
      ResourceHolder::getInstance().getFont(), color);
  utils::Utils::prepareText(m_energy_cost_prefix, ENERGY_COST_STRING_PREFIX, 32,
      ResourceHolder::getInstance().getFont(), color);

  sf::FloatRect bounds = m_energy_used_prefix.getLocalBounds();

  m_power_prefix.setPosition(1180.0f - bounds.width / 2.0f + m_power_prefix.getLocalBounds().width / 2, 3 * m_sprite.getLocalBounds().height / 2);
  m_usage_time_prefix.setPosition(1180.0f - bounds.width / 2.0f + m_usage_time_prefix.getLocalBounds().width / 2, 5 * m_sprite.getLocalBounds().height / 2);
  m_energy_used_prefix.setPosition(1180.0f - bounds.width / 2.0f + m_energy_used_prefix.getLocalBounds().width / 2, 7 *  m_sprite.getLocalBounds().height / 2);
  m_energy_cost_prefix.setPosition(1180.0f - bounds.width / 2.0f + m_energy_cost_prefix.getLocalBounds().width / 2, 9 * m_sprite.getLocalBounds().height / 2);

}

void RoomViewItem::drawInfo(sf::RenderTarget& target, sf::RenderStates states, sf::RectangleShape& background) {
  auto bounds = background.getGlobalBounds();

  m_text_power->setPosition(bounds.left + bounds.width / 2.f, bounds.top + 3 * m_sprite.getLocalBounds().height / 2);
  m_text_time->setPosition(bounds.left + bounds.width / 2.f, bounds.top + 5 * m_sprite.getLocalBounds().height / 2);
  m_text_energy_used.setPosition(bounds.left + bounds.width / 2.f, bounds.top + 7 * m_sprite.getLocalBounds().height / 2);
  m_text_energy_cost.setPosition(bounds.left + bounds.width / 2.f, bounds.top + 9 * m_sprite.getLocalBounds().height / 2);

  m_text_power->draw(target);
  m_text_time->draw(target);
  target.draw(m_power_prefix, states);
  target.draw(m_usage_time_prefix, states);
  target.draw(m_energy_used_prefix, states);
  target.draw(m_energy_cost_prefix, states);
  target.draw(m_text_energy_used, states);
  target.draw(m_text_energy_cost, states);
}

sf::FloatRect RoomViewItem::getGlobalBoundsOfExitIcon() {
  auto bounds = m_exit_sprite.getGlobalBounds();
  bounds.left += settings::LISTVIEW_WIDTH;
  return bounds;
}

void RoomViewItem::update() {
  std::string str = m_text_power->getString();
  std::string str_2 = m_text_time->getString();
  std::string str_3 = m_text_name->getString();
  double power = 0.0f;
  try {
    power = std::stod(str);
  } catch (...) {
  }
  if (power < 30000.0) {
    m_device.setPower(power);
  }
  if (str.empty()) {
    m_text_power->setString("0");
  }
  m_device.setName(str_3);
  m_device.setUsageTime(str_2);
  m_text_energy_used.setString(utils::Utils::to_string(m_device.getEnergyInKwh()));
  m_text_energy_cost.setString(utils::Utils::to_string(m_device.getEnergyCost()));
  m_text_name->deactivate();
}

} /* namespace GUI */
