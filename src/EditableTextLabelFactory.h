#ifndef EDITABLETEXTLABELFACTORY_H_
#define EDITABLETEXTLABELFACTORY_H_
#include "EditableTextLabel.h"
#include "Singleton.h"
#include <memory>


namespace model {

class EditableTextLabelFactory : public core::Singleton<EditableTextLabelFactory> {
  public:
    static std::shared_ptr<GUI::EditableTextLabel> createEditableTextLabel(sf::Text text, size_t max_size = 10);

    class EditableTextLabelManager {
      public:
        EditableTextLabelManager() : m_active_item(nullptr) {}

        void addItem(std::shared_ptr<GUI::EditableTextLabel> item) {
          m_items.push_back(item);
        }

        bool isActiveItemSet() {
          return (m_active_item != nullptr) ? true : false;
        }

        void onMouseClicked(sf::Vector2f cursor, GUI::VIEW_ENUM view) {
          bool handled = false;
          for (auto item : m_items) {
            if (item->contains(cursor, view) && item->isSelectable()) {

              if (m_active_item != nullptr && m_active_item != item) {
                m_active_item->changeState();
                m_active_item = nullptr;
              }

              item->changeState();
              m_active_item = item;
              handled = true;
            }
          }

         if (!handled && m_active_item != nullptr) {
           m_active_item->changeState();
           m_active_item = nullptr;
         }
        }

        void onKeyPressed(sf::Event event) {
          if(event.type == sf::Event::TextEntered) {
            sf::Uint32 unicode = event.text.unicode;
            if ((unicode >= 46 && unicode <= 58) || (unicode >= 65 && unicode <= 90) || (unicode >= 97 && unicode <= 122)) {
              auto string = m_active_item->getString();
              if (string.size() < m_active_item->getMaxLength()) {
                string += static_cast<char>(unicode);
                m_active_item->setString(string);
              }
            }
          } else if(event.type == sf::Event::KeyPressed) {
            if(event.key.code == sf::Keyboard::BackSpace) {
              auto string = m_active_item->getString();
              if (!string.empty()) {
                string.pop_back();
                m_active_item->setString(string);
              }
            }
          }
        }

      private:
        std::shared_ptr<GUI::EditableTextLabel> m_active_item;
        std::vector<std::shared_ptr<GUI::EditableTextLabel>> m_items;
        sf::Clock m_clock;
    };

    static EditableTextLabelManager m_label_manager;
};



} /* namespace model */

#endif /* EDITABLETEXTLABELFACTORY_H_ */
