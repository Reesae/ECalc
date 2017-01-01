#ifndef STATVIEWIMPL_H_
#define STATVIEWIMPL_H_
#include "ListView.h"
#include "StatView.h"

namespace GUI {

class StatViewImpl {
  public:
    StatViewImpl();
    void onRoomViewChanged(double energy, double cost);
    void setCallback(std::function<void (double)> callback);
    void update();
    void onMouseClicked(sf::Vector2f vec) {};

    sf::View m_view;
    StatView m_statview;
};

} /* namespace GUI */

#endif /* STATVIEWIMPL_H_ */
