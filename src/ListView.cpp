#include "ListView.h"
#include "RoomViewImpl.h"

namespace GUI {

ListView::ListView() : m_root(nullptr), m_offset(0.0f) {

}

void ListView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  if (m_root == nullptr) {
    for (auto item : m_childrens) {
      target.draw(*(item.get()), states);
    }
  } else {
    for (auto item : m_root->getChildrens()) {
      target.draw(*(item.get()), states);
    }
  }
}

void ListView::checkCollision(sf::Vector2f& cursor) {
  sf::Time time1 = m_clock.getElapsedTime();
  if (time1.asMilliseconds() > 125) {
    if (m_root == nullptr) {
      for (auto item : m_childrens) {
        auto bounds = item->getGlobalBounds();
        bounds.top += m_offset;
          if (bounds.contains(cursor)) {
            setRootItem(item);
            m_offset = 0;
          }
      }
    } else {
      for (auto item : m_root->getChildrens()) {
        auto bounds = item->getGlobalBounds();
        bounds.top += m_offset;
        if (bounds.contains(cursor)) {
          m_callback(*(item->getDevice()));
        }
      }
    }
    m_clock.restart();
  }
}

void ListView::updateOffset(int offset) {
  m_offset += offset;
}

void ListView::setCallback(std::function<void (model::Device)> callback) {
  m_callback = callback;
}

void ListView::setRootItem(std::shared_ptr<ListViewItem> root) {
  m_root = (root != nullptr) ? root : nullptr;
}

} /* namespace GUI */

