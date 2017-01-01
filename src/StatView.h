#ifndef STATVIEW_H_
#define STATVIEW_H_

#include <SFML/Graphics.hpp>
#include "EditableTextLabel.h"
#include <string>
#include <memory>

namespace GUI {

class StatView : public sf::Drawable, public sf::NonCopyable {
  public:
    StatView();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void setEnergy(double energy) {m_energy = energy;}
    void setCost(double cost) {m_cost = cost;}
    void update();
  private:
    double m_energy;
    double m_cost;
    double m_price;

    std::shared_ptr<EditableTextLabel> m_energy_price_text;
    sf::RectangleShape m_background;
    sf::Text m_energy_used;
    sf::Text m_energy_produced;
    sf::Text m_balance;
    sf::Text m_energy_price_prefix;
    sf::Text m_emission;
    sf::Text m_tree_info;

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

#endif /* STATVIEW_H_ */
