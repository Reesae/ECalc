#ifndef ROOMVIEWIMPL_H_
#define ROOMVIEWIMPL_H_
#include "RoomView.h"
#include <SFML/Graphics/View.hpp>

namespace GUI {

class RoomViewImpl {
  public:
    RoomViewImpl();
    void onMouseClicked(sf::Vector2f& vec);
    void onKeyPressed(sf::Event event);
    void addDeviceToActiveRoom(model::Device device = model::Device("device", 0.0f, "00:00"));
    void addRoomToRoomView();
    void update();
    sf::View m_view;
    RoomView m_roomview;

};

} /* namespace GUI */

#endif /* ROOMVIEW_H_ */
