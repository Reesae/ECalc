#include "EventHandler.h"
#include "Settings.h"
#include "EditableTextLabelFactory.h"

namespace core {
EventHandler::EventHandler(sf::Window& window, GUI::GUIManager& manager) : m_window(window), m_gui(manager) {
  using namespace std::placeholders;
  m_listview_leftmouseclicked = std::bind(GUI::ListViewImpl::onLeftMouseClicked, &m_gui.m_listview, _1);
  m_listview_rightmouseclicked = std::bind(GUI::ListViewImpl::onRightMouseClicked, &m_gui.m_listview);
  m_listview_mousescrolled = std::bind(GUI::ListViewImpl::onMouseScrolled, &m_gui.m_listview, _1);
  m_roomview_mouseclicked = std::bind(GUI::RoomViewImpl::onMouseClicked, &m_gui.m_roomview, _1);
  m_statview_mouseclicked = std::bind(GUI::StatViewImpl::onMouseClicked, &m_gui.m_statview, _1);
}

void EventHandler::onMouseClicked(sf::Event& event) {
  auto cursor = static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window));

  if (isInsideListViewBounds(cursor)) {

    if (event.mouseButton.button == sf::Mouse::Button::Left) {
    m_listview_leftmouseclicked(cursor);
    } else if (event.mouseButton.button == sf::Mouse::Button::Right) {
      m_listview_rightmouseclicked();
    }

  } else if (isInsideStatViewBounds(cursor)) {
    m_statview_mouseclicked(cursor);
    model::EditableTextLabelFactory::getInstance().m_label_manager.onMouseClicked(cursor, GUI::VIEW_ENUM::STATVIEW);
  } else if (isInsideRoomViewBounds(cursor)) {
    m_roomview_mouseclicked(cursor);
    model::EditableTextLabelFactory::getInstance().m_label_manager.onMouseClicked(cursor, GUI::VIEW_ENUM::ROOMVIEW);
  }
}

void EventHandler::onMouseScrolled(sf::Event& event) {
  auto cursor = static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window));
  if (isInsideListViewBounds(cursor)) {
    m_listview_mousescrolled(event);
  }
}

void EventHandler::onTextEntered(sf::Event& event) {
  if (model::EditableTextLabelFactory::getInstance().m_label_manager.isActiveItemSet()) {
    model::EditableTextLabelFactory::getInstance().m_label_manager.onKeyPressed(event);
  } else {
    m_gui.m_roomview.onKeyPressed(event);
  }
}

void EventHandler::globalEvents() {
  //model::EditableTextLabelFactory::getInstance().m_label_manager.insertionPointBlink();
}

bool EventHandler::isInsideListViewBounds(sf::Vector2f& vec) {
  return (vec.x <= settings::LISTVIEW_WIDTH && vec.y <= settings::LISTVIEW_HEIGHT) ? true : false;
}

bool EventHandler::isInsideRoomViewBounds(sf::Vector2f& vec) {
  return (vec.x > settings::VIDEO_WIDTH - settings::ROOMVIEW_WIDTH && vec.y <= settings::ROOMVIEW_HEIGHT) ? true : false;
}

bool EventHandler::isInsideStatViewBounds(sf::Vector2f& vec) {
  return (vec.x > 1180.f && vec.y > settings::VIDEO_HEIGHT - settings::STATVIEW_HEIGHT) ? true : false;
}

} /* namespace core */
