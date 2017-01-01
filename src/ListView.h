#ifndef GUI_LISTVIEW_H_
#define GUI_LISTVIEW_H_

#include "ListViewItem.h"
#include "Room.h"
#include <SFML/Graphics.hpp>
#include <functional>

namespace GUI {

class ListView : public sf::Drawable, public sf::NonCopyable {
  public:
    ListView();
    inline void insert(std::shared_ptr<ListViewItem> item) {m_childrens.push_back(item);}
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void checkCollision(sf::Vector2f& cursor);
    void updateOffset(int offset);
    int getOffset() {return m_offset;}
    void setCallback(std::function<void (model::Device)> callback);
    void setRootItem(std::shared_ptr<ListViewItem> root = nullptr);
  private:
    std::vector<std::shared_ptr<ListViewItem>> m_childrens;
    std::shared_ptr<ListViewItem> m_root;
    int m_offset;
    sf::Clock m_clock;
    std::function<void (model::Device)> m_callback;

};

} /* namespace GUI */

#endif /* GUI_LISTVIEW_H_ */
