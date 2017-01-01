#include "GUIManager.h"

namespace GUI {

GUIManager::GUIManager(sf::RenderWindow& window) :m_listview(), m_roomview(), m_statview(), m_window(window) {
  using namespace std::placeholders;
  auto callback = std::bind(RoomViewImpl::addDeviceToActiveRoom, &m_roomview, _1);
  m_listview.m_listviewmodel.setCallback(callback);

  auto callback2 = std::bind(StatViewImpl::onRoomViewChanged, &m_statview, _1, _2);
  m_roomview.m_roomview.setCallback(callback2);
}

void GUIManager::draw(sf::RenderStates& states) {
  sf::RectangleShape background;
  sf::Color gray (192, 192, 192);
  background.setFillColor(gray);
  background.setSize(sf::Vector2f(1920.f, 2180.f));
  background.setPosition(-100.f, -100.f);
  background.setOutlineColor(sf::Color::Black);
  background.setOutlineThickness(1.0f);

  m_statview.update();
  m_roomview.update();
  m_window.setView(m_listview.m_view);
  m_window.draw(background);
  m_window.draw(m_listview.m_listviewmodel, states);
  m_window.setView(m_roomview.m_view);
  m_window.draw(background);
  m_window.draw(m_roomview.m_roomview, states);
  m_window.setView(m_statview.m_view);
  m_window.draw(background);
  m_window.draw(m_statview.m_statview, states);


}

} /* namespace GUI */
