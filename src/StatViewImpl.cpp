#include "StatViewImpl.h"
#include "Settings.h"

namespace GUI {

StatViewImpl::StatViewImpl() : m_view(sf::FloatRect(0.0f, 0.0f, settings::STATVIEW_WIDTH, settings::STATVIEW_HEIGHT)) {
  m_view.setViewport(sf::FloatRect(settings::STATVIEW_START_POS_X, settings::STATVIEW_START_POS_Y,
      settings::STATVIEW_RELATIVE_WIDTH, settings::STATVIEW_RELATIVE_HEIGHT));
}

void StatViewImpl::onRoomViewChanged(double energy, double cost) {
  m_statview.setEnergy(energy);
  m_statview.setCost(cost);
}

void StatViewImpl::update() {
  m_statview.update();
}


} /* namespace GUI */
