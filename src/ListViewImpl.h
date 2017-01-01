#ifndef LISTVIEWIMPL_H_
#define LISTVIEWIMPL_H_
#include "ListView.h"
#include "ListViewItemsFactory.h"

namespace GUI {

class ListViewImpl {
  public:
    ListViewImpl();
    void onLeftMouseClicked(sf::Vector2f& cursor);
    void onRightMouseClicked();

    void onMouseScrolled(sf::Event& event);
    bool contains(sf::Vector2f& vector);
    sf::View m_view;
    ListView m_listviewmodel;
};

} /* namespace GUI */

#endif /* LISTVIEWIMPL_H_ */
