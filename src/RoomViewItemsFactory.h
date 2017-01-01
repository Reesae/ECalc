#ifndef ROOMVIEWITEMSFACTORY_H_
#define ROOMVIEWITEMSFACTORY_H_
#include "RoomView.h"

namespace GUI {

class RoomViewItemsFactory {
  public:
     static std::shared_ptr<RoomViewItem> buildRoomViewItem(std::shared_ptr<Room> room);
     static std::shared_ptr<RoomViewItem> buildRoomViewItem(model::Device device, RoomView& roomview);
     static void buildRoomViewStructure(RoomView& roomview);
     static void addEmptyRoomToRoomView(RoomView& roomview);

   private:
     class ResourceHolder {
       public:
       ResourceHolder() {
         m_texture.loadFromFile("resources/texture.png", sf::IntRect(0, 216, 500, 72));
         m_large_texture.loadFromFile("resources/texture.png", sf::IntRect(0, 288, 500, 144));
         m_exit_icon_texture.loadFromFile("resources/texture.png", sf::IntRect(0, 288 + 142, 28, 28));
         m_sprite.setTexture(m_texture);
         m_large_sprite.setTexture(m_large_texture);
         m_exit_icon.setTexture(m_exit_icon_texture);
       }

       static ResourceHolder& getInstance() {
         static ResourceHolder res_holder;
         return res_holder;
       }

       sf::Sprite getSprite(int i) {
         if (i == 0) {
           return m_large_sprite;
         } else if (i == 1) {
           return m_sprite;
         } else return m_exit_icon;
       }

       sf::Texture m_texture;
       sf::Texture m_large_texture;
       sf::Texture m_exit_icon_texture;

       sf::Sprite m_sprite;
       sf::Sprite m_large_sprite;
       sf::Sprite m_exit_icon;

     };
};

} /* namespace GUI */

#endif /* ROOMVIEWITEMSFACTORY_H_ */
