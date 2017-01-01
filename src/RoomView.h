#ifndef ROOMVIEW_H_
#define ROOMVIEW_H_
#include "Room.h"

namespace GUI {

class RoomView : public sf::Drawable, public sf::NonCopyable {
  public:
    RoomView(sf::View& view);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void drawRooms(sf::RenderTarget& target, sf::RenderStates states) const;
    void drawItems(sf::RenderTarget& target, sf::RenderStates states) const;
    void drawItemInfo(sf::RenderTarget& target, sf::RenderStates states) const;
    void update();
    void appendRoom(std::shared_ptr<Room> room);
    std::shared_ptr<Room> getCurrentRoom();
    void nextRoom();
    void previousRoom();
    void checkItemsCollision(sf::Vector2f& cursor);
    void checkRoomsCollision(sf::Vector2f& cursor);
    void checkForDeletion(sf::Vector2f& cursor);
    void changeRoom(std::shared_ptr<Room> room);
    void setCallback(std::function<void (double, double)> callback);
    void roomViewChanged();
    double getTotalEnergy();
    double getTotalCost();
    void removeRoom(std::vector<std::shared_ptr<Room>>::iterator itr);
    size_t getRoomsCount();
  private:
    sf::View& m_view;
    std::shared_ptr<Room> m_current_room;

    std::vector<std::shared_ptr<Room>> m_rooms;
    std::function<void (double, double)> m_statview_notify_changed;

};

} /* namespace GUI */

#endif /* ROOMVIEW_H_ */
