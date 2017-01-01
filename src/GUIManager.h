#ifndef GUIMANAGER_H_
#define GUIMANAGER_H_
#include "ListViewImpl.h"
#include "RoomViewImpl.h"
#include "StatViewImpl.h"

namespace GUI {

class GUIManager {
  public:
    GUIManager(sf::RenderWindow& window);
    void draw(sf::RenderStates& states);
    ListViewImpl m_listview;
    RoomViewImpl m_roomview;
    StatViewImpl m_statview;

  private:
    sf::RenderWindow& m_window;
};

} /* namespace GUI */

#endif /* GUIMANAGER_H_ */
