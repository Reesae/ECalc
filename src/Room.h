#ifndef ROOM_H_
#define ROOM_H_
#include "EditableTextLabelFactory.h"
#include "RoomViewItem.h"

namespace GUI {

class Room : public Component {
  public:
    Room(sf::Sprite m_sprite, sf::Sprite exit_icon, std::string& name);
    ~Room();
    virtual bool isSelectable() const override;
    virtual void select();
    virtual void deselect();
    virtual void activate();
    virtual void deactivate();
    virtual void handleEvent(const sf::Event& event) override;
    void setPosition(float x, float y);
    void move(float x, float y);
    void drawItems(sf::RenderTarget& target, sf::RenderStates states) const;
    void drawItemInfo(sf::RenderTarget& target, sf::RenderStates states) const;
    void update();
    void appendItem(std::shared_ptr<RoomViewItem> roomviewitem);
    void setActiveItem(std::shared_ptr<RoomViewItem> item);
    std::vector<std::shared_ptr<RoomViewItem>>& getItems();
    sf::FloatRect getGlobalBounds();
    double getTotalEnergy();
    double getTotalCost();
    double getTotalPower();
    void itemChanged();
    sf::FloatRect getGlobalBoundsOfExitIcon();
    void removeRoomViewItem(std::vector<std::shared_ptr<RoomViewItem>>::iterator itr);
    void changeItem(std::shared_ptr<RoomViewItem> item);

  private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    std::string m_name;
    std::vector<std::shared_ptr<RoomViewItem>> m_items;
    std::shared_ptr<RoomViewItem> m_current_item;
    sf::Sprite m_sprite;
    sf::Sprite m_exit_sprite;
    std::shared_ptr<EditableTextLabel> m_text_name;
    sf::Text m_text_items_count;
    sf::Text m_text_power;
    sf::Text m_text_cost;

    class ResourceHolder {
      public:
        ResourceHolder() {
          m_font.loadFromFile("resources/BebasNeue.otf");
        }

        static ResourceHolder& getInstance() {
          static ResourceHolder res_holder;
          return res_holder;
        }

        sf::Font& getFont() {
          return m_font;
        }

        sf::Font m_font;
    };
};

} /* namespace GUI */

#endif /* ROOM_H_ */
