#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics.hpp>

#include <memory>

namespace sf {
	class Event;
}

namespace GUI {

class Component : public sf::Drawable, public sf::Transformable, private sf::NonCopyable {
	public:
    Component();
    virtual	~Component();
    virtual bool isSelectable() const = 0;
    bool isSelected() const;
    virtual void select();
    virtual void deselect();
    virtual bool isActive() const;
    virtual void activate();
    virtual void deactivate();
    virtual void handleEvent(const sf::Event& event) = 0;

  private:
    bool m_selected;
    bool m_active;
};
}
#endif // COMPONENT_HPP
