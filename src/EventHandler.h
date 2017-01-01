#ifndef EVENTHANDLER_H_
#define EVENTHANDLER_H_

#include "GUIManager.h"

namespace core {

class EventHandler {
  public:
    EventHandler(sf::Window& window, GUI::GUIManager& manager);
    void onMouseClicked(sf::Event& event);
    void onMouseScrolled(sf::Event& event);
    void onTextEntered(sf::Event& event);
    void globalEvents();
  private:
    bool isInsideListViewBounds(sf::Vector2f& vec);
    bool isInsideRoomViewBounds(sf::Vector2f& vec);
    bool isInsideStatViewBounds(sf::Vector2f& vec);


    std::function<void (sf::Vector2f&)> m_listview_leftmouseclicked;
    std::function<void ()> m_listview_rightmouseclicked;
    std::function<void (sf::Vector2f&)> m_roomview_mouseclicked;
    std::function<void (sf::Vector2f&)> m_statview_mouseclicked;
    std::function<void (sf::Event&)> m_listview_mousescrolled;
    sf::Window& m_window;
    GUI::GUIManager& m_gui;
};

} /* namespace core */

#endif /* EVENTHANDLER_H_ */
