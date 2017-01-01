#include "Component.h"

namespace GUI {

Component::Component() : m_selected(false), m_active(false) {
}

Component::~Component() {
}

bool Component::isSelected() const {
  return m_selected;
}

void Component::select() {
  m_selected = true;
}

void Component::deselect() {
  m_selected = false;
}

bool Component::isActive() const {
  return m_active;
}

void Component::activate() {
  m_active = true;
}

void Component::deactivate() {
  m_active = false;
}

}
