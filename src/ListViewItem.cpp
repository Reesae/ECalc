#include "ListViewItem.h"
#include "Utils.h"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <cmath>

namespace GUI {


ListViewItem::ListViewItem() {
  sf::FloatRect bounds = m_sprite.getGlobalBounds();
  m_text.setPosition(bounds.width / 2.f, bounds.height / 2.f);
}

ListViewItem::ListViewItem(sf::Sprite sprite, sf::Text text, std::string name)
  : m_sprite(sprite), m_text(text), m_device(nullptr) {
  sf::FloatRect bounds = m_sprite.getGlobalBounds();
  auto color = sf::Color::Red;
  utils::Utils::prepareText(m_text, name, 32, ResourceHolder::getInstance().getFont(), color);
  m_text.setPosition(bounds.width / 2.f, bounds.height / 2.f);
}

ListViewItem::ListViewItem(sf::Sprite sprite, sf::Text text, std::shared_ptr<model::Device> device)
  : m_sprite(sprite), m_text(text), m_device(device) {
  sf::FloatRect bounds = m_sprite.getGlobalBounds();
  auto color = sf::Color::Red;
  utils::Utils::prepareText(m_text, m_device->getName(), 32, ResourceHolder::getInstance().getFont(), color);
  m_text.setPosition(bounds.width / 2.f, bounds.height / 2.f);
}

ListViewItem::~ListViewItem() {
}

bool ListViewItem::isSelectable() const {
  return true;
}

void ListViewItem::select() {
  Component::select();
}

void ListViewItem::deselect() {
  Component::select();
}

void ListViewItem::activate() {
  if (m_callback)
    m_callback();
}

void ListViewItem::deactivate() {
}

void ListViewItem::handleEvent(const sf::Event& event) {
}

void ListViewItem::setCallback(Callback callback) {
  m_callback = std::move(callback);
}

void ListViewItem::setText(const std::string& text) {
  m_text.setString(text);

  sf::FloatRect bounds = m_text.getGlobalBounds();
  m_text.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

void ListViewItem::draw(sf::RenderTarget& target, sf::RenderStates states) const {

  states.transform *= getTransform();
  target.draw(m_sprite, states);
  target.draw(m_text, states);
}

void ListViewItem::appendChild(std::shared_ptr<ListViewItem> child) {
  m_childrens.push_back(child);
}

sf::FloatRect ListViewItem::getGlobalBounds() {
  sf::Vector2f size(this->m_sprite.getGlobalBounds().width, this->m_sprite.getGlobalBounds().height);
  return sf::FloatRect(this->getPosition(), size);
}

std::vector<std::shared_ptr<ListViewItem>> ListViewItem::getChildrens() {
  return m_childrens;
}
std::shared_ptr<model::Device> ListViewItem::getDevice() {
  return m_device;
}
}
