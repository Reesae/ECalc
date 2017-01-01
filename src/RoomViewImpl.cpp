#include "RoomViewImpl.h"
#include "RoomViewItemsFactory.h"
#include "Settings.h"

namespace GUI {

RoomViewImpl::RoomViewImpl() : m_view(sf::FloatRect(0.0f, 0.0f, settings::ROOMVIEW_WIDTH, settings::ROOMVIEW_HEIGHT)),
    m_roomview(m_view) {
  m_view.setViewport(sf::FloatRect(0.156f, 0.0f, settings::ROOMVIEW_RELATIVE_WIDTH, settings::ROOMVIEW_RELATIVE_HEIGHT));
  RoomViewItemsFactory::buildRoomViewStructure(m_roomview);
}

void RoomViewImpl::onMouseClicked(sf::Vector2f& vec) {
  m_roomview.checkForDeletion(vec);
  m_roomview.checkRoomsCollision(vec);
  m_roomview.checkItemsCollision(vec);
}

void RoomViewImpl::onKeyPressed(sf::Event event) {
  if (event.key.code == sf::Keyboard::R) {
    addRoomToRoomView();
  } else if (event.key.code == sf::Keyboard::D) {
    addDeviceToActiveRoom();
  }
}

void RoomViewImpl::addDeviceToActiveRoom(model::Device device) {
  if (m_roomview.getCurrentRoom() != nullptr) {
    auto item = RoomViewItemsFactory::buildRoomViewItem(device, m_roomview);
    m_roomview.getCurrentRoom()->appendItem(item);
  }
}

void RoomViewImpl::addRoomToRoomView() {
  GUI::RoomViewItemsFactory::addEmptyRoomToRoomView(m_roomview);
}

void RoomViewImpl::update() {
  m_roomview.update();
}


} /* namespace GUI */
