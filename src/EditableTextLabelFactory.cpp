#include "EditableTextLabelFactory.h"

namespace model {

EditableTextLabelFactory::EditableTextLabelManager EditableTextLabelFactory::m_label_manager = {};

std::shared_ptr<GUI::EditableTextLabel> EditableTextLabelFactory::createEditableTextLabel(sf::Text text, size_t max_size) {
  auto item = std::make_shared<GUI::EditableTextLabel>(text, max_size);
  m_label_manager.addItem(item);
  return item;
}
} /* namespace model */
