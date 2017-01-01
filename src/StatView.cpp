#include "StatView.h"
#include "Settings.h"
#include "Utils.h"
#include "Device.h"
#include "EditableTextLabelFactory.h"
#include <cmath>

namespace GUI {
static const std::string TOTAL_ENERGY_USED_PREFIX = "Total energy used: ";
static const std::string TOTAL_ENERGY_PRODUCED_PREFIX = "Total energy produced: ";
static const std::string ENERGY_UNIT = "KWH";

StatView::StatView() : m_energy(0), m_cost(0), m_price(0.60) {
  sf::Color gray (220, 220, 220);
  m_background.setFillColor(gray);
  m_background.setSize(sf::Vector2f(577.f, 537.f));
  m_background.setPosition(3.f, 3.f);
  m_background.setOutlineColor(sf::Color::Black);
  m_background.setOutlineThickness(3.0f);

  utils::Utils::prepareText(m_energy_used, TOTAL_ENERGY_USED_PREFIX + utils::Utils::to_string(m_energy / model::JOULES_TO_KWH) + ENERGY_UNIT,
       32, ResourceHolder::getInstance().getFont(), gray);
   utils::Utils::prepareText(m_energy_produced, TOTAL_ENERGY_PRODUCED_PREFIX + "0.00kWh",
       32, ResourceHolder::getInstance().getFont(), gray);
   utils::Utils::prepareText(m_balance, "Balance: -" + utils::Utils::to_string(m_cost) + "$",
       32, ResourceHolder::getInstance().getFont(), gray);
   utils::Utils::prepareText(m_energy_price_prefix, "Price of kWh: ",
       32, ResourceHolder::getInstance().getFont(), gray);
   utils::Utils::prepareText(m_emission, "CO2 emitted [kg]: " + utils::Utils::to_string(0.781 * m_energy / model::JOULES_TO_KWH),
       32, ResourceHolder::getInstance().getFont(), gray);
   utils::Utils::prepareText(m_tree_info, "Tree's to absorb CO2: " + utils::Utils::to_string(0.781 * m_energy / model::JOULES_TO_KWH / 23.81, 0),
       32, ResourceHolder::getInstance().getFont(), gray);

   sf::Text energy_price;
   utils::Utils::prepareText(energy_price, "0.60",
       32, ResourceHolder::getInstance().getFont(), gray);

   m_energy_price_text = model::EditableTextLabelFactory::createEditableTextLabel(energy_price, 4);
   m_energy_price_text->activate();

   sf::FloatRect bounds = m_energy_used.getLocalBounds();
   m_energy_price_prefix.setPosition(190.0f - bounds.width / 2.0f + m_energy_price_prefix.getLocalBounds().width / 2, bounds.top + 36);
   m_energy_price_text->setPosition(190.0f - bounds.width / 2.0f + m_energy_price_prefix.getLocalBounds().width + 25, bounds.top + 36);
   m_energy_used.setPosition(190.0f - bounds.width / 2.0f + m_energy_used.getLocalBounds().width / 2, bounds.top + 108);
   m_energy_produced.setPosition(190.0f - bounds.width / 2.0f + m_energy_produced.getLocalBounds().width / 2, bounds.top + 180);
   m_balance.setPosition(190.0f - bounds.width / 2.0f + m_balance.getLocalBounds().width / 2, bounds.top + 252);
   m_emission.setPosition(190.0f - bounds.width / 2.0f + m_emission.getLocalBounds().width / 2, bounds.top + 324);
   m_tree_info.setPosition(190.0f - bounds.width / 2.0f + m_tree_info.getLocalBounds().width / 2, bounds.top + 396);

}

void StatView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(m_background);
  target.draw(m_energy_used);
  target.draw(m_energy_produced);
  target.draw(m_balance);
  target.draw(m_energy_price_prefix);
  target.draw(m_emission);
  target.draw(m_tree_info);
  m_energy_price_text->draw(target);
}

void StatView::update() {
  std::string str = m_energy_price_text->getString();
  double price = 0.0f;
  try {
    price = std::stod(str);
  } catch (...) {
  }
  if (price != m_price) {
    m_price = price;
    model::Device::setPrice(price);
  }

  m_energy_used.setString(TOTAL_ENERGY_USED_PREFIX + utils::Utils::to_string(m_energy / model::JOULES_TO_KWH) + ENERGY_UNIT);
  m_energy_produced.setString(TOTAL_ENERGY_PRODUCED_PREFIX + "0.00kWh");
  m_balance.setString("Balance: -" + utils::Utils::to_string(m_cost) + "$");
  m_emission.setString("CO2 emitted [kg]: " + utils::Utils::to_string(0.781 * m_energy / model::JOULES_TO_KWH));
  m_tree_info.setString("Tree's to absorb CO2: " + utils::Utils::to_string(0.781 * m_energy / model::JOULES_TO_KWH / 23.81, 0));


}

} /* namespace GUI */
