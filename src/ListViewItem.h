#ifndef GUI_LISTVIEWITEM_H_
#define GUI_LISTVIEWITEM_H_

#include "Component.h"
#include "Device.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <functional>

namespace GUI {

class ListViewItem : public Component {
  public:
    typedef std::function<void()> Callback;

    ListViewItem();
    ListViewItem(sf::Sprite sprite, sf::Text text, std::string name);
    ListViewItem(sf::Sprite sprite, sf::Text text, std::shared_ptr<model::Device> device);
    virtual ~ListViewItem();
    virtual bool isSelectable() const override;
    virtual void select();
    virtual void deselect();
    virtual void activate();
    virtual void deactivate();
    virtual void handleEvent(const sf::Event& event) override;
    void setCallback(Callback callback);
    void setText(const std::string& text);
    void appendChild(std::shared_ptr<ListViewItem> child);
    sf::FloatRect getGlobalBounds();
    std::vector<std::shared_ptr<ListViewItem>> getChildrens();
    std::shared_ptr<model::Device> getDevice();
    private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::Sprite m_sprite;
    sf::Text m_text;
    Callback m_callback;
    std::vector<std::shared_ptr<ListViewItem>> m_childrens;
    std::shared_ptr<model::Device> m_device;

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

}
#endif /* LISTVIEWITEM_H_ */
