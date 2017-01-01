#ifndef ROOMVIEWITEM_H_
#define ROOMVIEWITEM_H_
#include "Component.h"
#include "Device.h"
#include "EditableTextLabelFactory.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <functional>
#include <cmath>

namespace GUI {

class RoomViewItem: public Component {
  public:
    RoomViewItem(sf::Sprite sprite, sf::Sprite icon, model::Device device);
    virtual ~RoomViewItem();
    virtual bool isSelectable() const;
    virtual void select();
    virtual void deselect();
    virtual void activate();
    virtual void deactivate();
    virtual void handleEvent(const sf::Event& event);
    void move(float x, float y);
    void setPosition(float x, float y);
    void setText(const std::string& text);
    sf::FloatRect getGlobalBounds();
    model::Device& getDevice();
    void drawInfo(sf::RenderTarget& target, sf::RenderStates states, sf::RectangleShape& background);
    sf::Text getItemName() {return m_text_name->getTextCopy();}
    sf::FloatRect getGlobalBoundsOfExitIcon();
    void update();

    private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void preparePrefixText();
    void prepareText();

    sf::Sprite m_sprite;
    sf::Sprite m_exit_sprite;
    std::shared_ptr<EditableTextLabel> m_text_name;
    std::shared_ptr<EditableTextLabel> m_text_power;
    std::shared_ptr<EditableTextLabel> m_text_time;
    sf::Text m_text_energy_used;
    sf::Text m_text_energy_cost;
    sf::Text m_power_prefix;
    sf::Text m_usage_time_prefix;
    sf::Text m_energy_used_prefix;
    sf::Text m_energy_cost_prefix;

    model::Device m_device;

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

#endif /* ROOMVIEWITEM_H_ */
