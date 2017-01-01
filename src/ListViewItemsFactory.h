#ifndef GUI_LISTVIEWITEMSFACTORY_H_
#define GUI_LISTVIEWITEMSFACTORY_H_

#include "ListView.h"
#include <tuple>

namespace GUI {

class ListViewItemsFactory {
  public:
    static std::shared_ptr<ListViewItem> buildKitchenListViewItem();
    static std::shared_ptr<ListViewItem> buildDeviceListViewItem(std::tuple<std::string, std::string, float>& item);

    static std::shared_ptr<ListViewItem> buildRootListViewItem();
    static void buildListViewStructure(ListView& listview);

    static std::vector<std::tuple<std::string, std::string, float>> m_devices_kitchen;
    static std::vector<std::tuple<std::string, std::string, float>> m_devices_living_room;
    static std::vector<std::tuple<std::string, std::string, float>> m_devices_bedroom;
    static std::vector<std::tuple<std::string, std::string, float>> m_devices_bathroom;
    static std::vector<std::tuple<std::string, std::string, float>> m_devices_laundry_room;
    static std::vector<std::tuple<std::string, std::string, float>> m_devices_outdoor;
    static std::vector<std::tuple<std::string, std::string, float>> m_devices_other;
  private:
    class ResourceHolder {
      public:
      ResourceHolder() {
        m_root_texture.loadFromFile("resources/texture.png", sf::IntRect(0, 0, 300, 108));
        m_child_texture.loadFromFile("resources/texture.png", sf::IntRect(0, 108, 300, 108));

        m_root_sprite.setTexture(m_root_texture);
        m_child_sprite.setTexture(m_child_texture);
      }

      static ResourceHolder& getInstance() {
        static ResourceHolder res_holder;
        return res_holder;
      }

      sf::Sprite getSprite(int i) {
        return i ? m_root_sprite : m_child_sprite;
      }

      sf::Texture m_root_texture;
      sf::Texture m_child_texture;
      sf::Sprite m_root_sprite;
      sf::Sprite m_child_sprite;
    };

};

}

#endif /* GUI_LISTVIEWITEMSFACTORY_H_ */
