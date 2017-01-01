#include "ListViewImpl.h"
#include "Utils.h"
#include "Settings.h"
#include <type_traits>

namespace GUI {

ListViewImpl::ListViewImpl() : m_view(sf::FloatRect(0.0f, 0.0f, settings::LISTVIEW_WIDTH, settings::LISTVIEW_HEIGHT)) {
  m_view.setViewport(sf::FloatRect(0.0f, 0.0f, settings::LISTVIEW_RELATIVE_WIDTH, settings::LISTVIEW_RELATIVE_HEIGHT));
  GUI::ListViewItemsFactory::buildListViewStructure(m_listviewmodel);

}

void ListViewImpl::onLeftMouseClicked(sf::Vector2f& cursor) {
  m_listviewmodel.checkCollision(cursor);
  m_view.reset(sf::FloatRect(0.0f, 0.0f, settings::LISTVIEW_WIDTH, settings::LISTVIEW_HEIGHT));
}

void ListViewImpl::onRightMouseClicked() {
  m_listviewmodel.setRootItem(nullptr);
}

void ListViewImpl::onMouseScrolled(sf::Event& event) {
  auto delta = event.mouseWheelScroll.delta;

  if (m_listviewmodel.getOffset() < 0 && delta > 0.0f) {
    m_view.move(0, -1 * settings::MOUSE_WHEEL_SCROLL_MULTPLIER * delta);
    m_listviewmodel.updateOffset(settings::MOUSE_WHEEL_SCROLL_MULTPLIER * delta);

  } else if (delta < 0.0f) {
    m_view.move(0, -1 * settings::MOUSE_WHEEL_SCROLL_MULTPLIER * delta);
    m_listviewmodel.updateOffset(settings::MOUSE_WHEEL_SCROLL_MULTPLIER * delta);
  }
}

bool ListViewImpl::contains(sf::Vector2f& vector) {
  return m_view.getViewport().contains(utils::Utils::scaleVecToView(vector));
}

} /* namespace GUI */
