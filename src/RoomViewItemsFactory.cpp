#include "RoomViewItemsFactory.h"

namespace GUI {

std::shared_ptr<RoomViewItem> RoomViewItemsFactory::buildRoomViewItem(std::shared_ptr<Room> room) {
  std::string name("device");
  float offset = 100.f * room->getItems().size();
  model::Device device(name, 1000.0, "01:00");
  auto item = std::make_shared<RoomViewItem>(ResourceHolder::getInstance().getSprite(1), ResourceHolder::getInstance().getSprite(2), device);

  return item;
}

std::shared_ptr<RoomViewItem> RoomViewItemsFactory::buildRoomViewItem(model::Device device, RoomView& roomview) {
  auto item = std::make_shared<RoomViewItem>(ResourceHolder::getInstance().getSprite(1), ResourceHolder::getInstance().getSprite(2), device);
  auto size = roomview.getCurrentRoom()->getItems().size();
  item->move(530.f, 0.f + 72.f * size);
  return item;
}

void RoomViewItemsFactory::buildRoomViewStructure(RoomView& roomview) {
  std::string name("room");
  std::string name2("room2");

  auto room = std::make_shared<Room>(ResourceHolder::getInstance().getSprite(0), ResourceHolder::getInstance().getSprite(2), name);
  auto room2 = std::make_shared<Room>(ResourceHolder::getInstance().getSprite(0), ResourceHolder::getInstance().getSprite(2), name2);

  room->move(10.f, 0.f);
  room2->move(10.f,146.f);

  auto factory = [&room](int n = 2) {
    do {
        auto item = buildRoomViewItem(room);
        item->move(530.f, 0.f + 72.f * std::abs(n - 2));
        room->appendItem(item);
      } while (--n);
    };

  auto factory2 = [&room2](int n = 2) {
    do {
        auto item = buildRoomViewItem(room2);
        item->move(530.f, 0.f + 72.f * std::abs(n - 2));
        room2->appendItem(item);
      } while (--n);
    };

    factory();
    factory2();

    room->setActiveItem(room->getItems().at(0));

    roomview.appendRoom(room);
    roomview.appendRoom(room2);
    roomview.changeRoom(room);

}

void RoomViewItemsFactory::addEmptyRoomToRoomView(RoomView& roomview) {
  std::string name("room");

  auto room = std::make_shared<Room>(ResourceHolder::getInstance().getSprite(0), ResourceHolder::getInstance().getSprite(2), name);
  room->move(10.0f, 146 * roomview.getRoomsCount());

  roomview.appendRoom(room);
  roomview.changeRoom(room);
}

} /* namespace GUI */
