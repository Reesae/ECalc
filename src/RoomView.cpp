#include "RoomView.h"

namespace GUI {

RoomView::RoomView(sf::View& view): m_view(view), m_current_room(nullptr) {

}

void RoomView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  drawRooms(target, states);
  drawItems(target, states);
  drawItemInfo(target, states);
}

void RoomView::drawRooms(sf::RenderTarget& target, sf::RenderStates states) const {
  if (!m_rooms.empty()) {
    for (auto room : m_rooms) {
      target.draw(*(room.get()), states);
    }
  }
}

void RoomView::drawItems(sf::RenderTarget& target, sf::RenderStates states) const {
  if (m_current_room != nullptr) {
    m_current_room->drawItems(target, states);
  }
}

void RoomView::drawItemInfo(sf::RenderTarget& target, sf::RenderStates states) const {
  if (m_current_room != nullptr) {
     m_current_room->drawItemInfo(target, states);
   }
}

void RoomView::update() {
  if (!m_rooms.empty()) {
    for (auto room : m_rooms) {
      room->update();
    }
  }
  roomViewChanged();
}

void RoomView::appendRoom(std::shared_ptr<Room> room) {
  m_rooms.push_back(room);
}

std::shared_ptr<Room> RoomView::getCurrentRoom() {
  return m_current_room;
}

void RoomView::checkRoomsCollision(sf::Vector2f& cursor) {
  if (!m_rooms.empty()) {
    for (auto room : m_rooms) {
      auto bounds = room->getGlobalBounds();
      if (bounds.contains(cursor)) {
        changeRoom(room);
        roomViewChanged();
        break;
      }
    }
  }
}

void RoomView::checkItemsCollision(sf::Vector2f& cursor) {
  if (m_current_room != nullptr && !m_rooms.empty()) {
    auto itr = m_current_room->getItems().begin();
    for ( ; itr != m_current_room->getItems().end(); ++itr) {
      auto bounds = (*itr)->getGlobalBounds();
      if (bounds.contains(cursor)) {
        m_current_room->setActiveItem(*itr);
        break;
      }
    }
  }
}

void RoomView::checkForDeletion(sf::Vector2f& cursor) {
  if (m_current_room != nullptr && !m_rooms.empty()) {
    auto itr = std::find_if(m_rooms.begin(), m_rooms.end(), [&](auto &item) {
      auto bounds = item->getGlobalBoundsOfExitIcon();
      return bounds.contains(cursor);
    });

    if (itr != m_rooms.end()) {
      changeRoom(itr != m_rooms.begin() ? *(itr - 1) : nullptr);
      removeRoom(itr);
    }

    if (m_current_room != nullptr) {
      auto& items = m_current_room->getItems();
      auto itr2 = std::find_if(items.begin(), items.end(), [&](auto &item) {
          auto bounds = item->getGlobalBoundsOfExitIcon();
          return bounds.contains(cursor);
      });

      if (itr2 != items.end()) {
        m_current_room->removeRoomViewItem(itr2);
    }
    }
  }
}

void RoomView::changeRoom(std::shared_ptr<Room> room) {
  m_current_room = room;
  if (m_current_room != nullptr) {
    if (!room->getItems().empty()) {
      room->setActiveItem(room->getItems()[0]);
    }
  }
}

void RoomView::setCallback(std::function<void (double, double)> callback) {
  m_statview_notify_changed = callback;
}

void RoomView::roomViewChanged() {
  double energy = getTotalEnergy();
  double cost = getTotalCost();
  m_statview_notify_changed(energy, cost);
}

double RoomView::getTotalEnergy() {
  double energy = 0.0;
  for (auto item : m_rooms) {
    energy += item->getTotalEnergy();
  }
  return energy;
}

double RoomView::getTotalCost() {
  double cost = 0.0;
  for (auto item : m_rooms) {
    cost += item->getTotalCost();
  }
  return cost;
}

void RoomView::removeRoom(std::vector<std::shared_ptr<Room>>::iterator itr) {
  auto itr_cpy = itr;
  for ( ; itr != m_rooms.end(); ++itr) {
    (*itr)->move(0.0f, -1 * (*itr)->getGlobalBounds().height);
  }
  m_rooms.erase(itr_cpy);
}

size_t RoomView::getRoomsCount() {
  return m_rooms.size();
}

} /* namespace GUI */
