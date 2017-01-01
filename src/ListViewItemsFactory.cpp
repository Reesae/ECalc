#include "ListViewItemsFactory.h"
#include "Device.h"

namespace GUI {

std::vector<std::tuple<std::string, std::string, float>> ListViewItemsFactory::m_devices_kitchen =
{std::make_tuple("Electric Cooker", "00:30", 2700.0f), std::make_tuple("Microwave", "00:05", 1500.0f),
std::make_tuple("Kettle", "00:10", 1500.0f), std::make_tuple("Toaster Oven", "00:05", 1200.0f),
std::make_tuple("Blender", "00:05", 300.0f), std::make_tuple("Ceiling Fan", "00:20", 100.0f),
std::make_tuple("LED Lightning", "01:00", 100.0f), std::make_tuple("CFL Lightning", "01:00", 125.0f),
std::make_tuple("Dishwasher", "00:20", 1200.0f), std::make_tuple("Coffee Machine", "00:05", 1500.0f),
std::make_tuple("Fridge-freezer A+", "24:00", 150.0f), std::make_tuple("Fridge-freezer C", "24:00", 300.0f),
std::make_tuple("Oven", "00:10", 3000.0f), std::make_tuple("Espresso Machine", "00:03", 400.0f)};

std::vector<std::tuple<std::string, std::string, float>> ListViewItemsFactory::m_devices_living_room =
{std::make_tuple("LED TV", "04:00", 80.0f), std::make_tuple("LCD TV", "04:00", 120.0f),
std::make_tuple("Plasma TV", "04:00", 200.0f), std::make_tuple("Desktop Computer", "04:00", 300.0f),
std::make_tuple("Laptop Computer", "04:00", 80.0f), std::make_tuple("Stereo", "00:20", 80.0f),
std::make_tuple("Mobile Device", "01:00", 5.0f), std::make_tuple("Electric Blanket", "00:15", 200.0f),
std::make_tuple("Game Console", "02:00", 100.0f), std::make_tuple("Modem", "08:00", 20.0f),
std::make_tuple("LED Lightning", "02:00", 150.0f), std::make_tuple("CFL Lightning", "02:00", 180.0f)};

std::vector<std::tuple<std::string, std::string, float>> ListViewItemsFactory::m_devices_bedroom =
{std::make_tuple("LED TV", "04:00", 80.0f), std::make_tuple("LCD TV", "04:00", 120.0f),
std::make_tuple("Plasma TV", "04:00", 200.0f), std::make_tuple("Desktop Computer", "04:00", 300.0f),
std::make_tuple("Laptop Computer", "04:00", 80.0f), std::make_tuple("Stereo", "00:20", 80.0f),
std::make_tuple("Mobile Device", "01:00", 5.0f), std::make_tuple("Electric Blanket", "00:15", 200.0f),
std::make_tuple("Game Console", "02:00", 100.0f), std::make_tuple("Modem", "08:00", 20.0f),
std::make_tuple("LED Lightning", "02:00", 150.0f), std::make_tuple("CFL Lightning", "02:00", 180.0f)};


std::vector<std::tuple<std::string, std::string, float>> ListViewItemsFactory::m_devices_bathroom =
{std::make_tuple("Water Heater", "01:00", 1000.0f), std::make_tuple("Hair Dryer", "00:05", 1500.0f),
std::make_tuple("Incandescent Lightning", "01:00", 300.0f),
std::make_tuple("LED Lighning", "01:00", 100.0f), std::make_tuple("CFL Lightning", "01:00", 130.0f),
std::make_tuple("Shaver", "00:05", 30.0f), std::make_tuple("Toothbrush", "00:05", 30.0f)};

std::vector<std::tuple<std::string, std::string, float>> ListViewItemsFactory::m_devices_laundry_room =
{std::make_tuple("Washing Machine", "00:30", 2000.0f), std::make_tuple("Iron", "00:15", 1000.0f),
std::make_tuple("Vacuum Cleaner", "00:10", 1000.0f), std::make_tuple("Incandescent Lightning", "01:00", 300.0f),
std::make_tuple("LED Lighning", "01:00", 100.0f), std::make_tuple("CFL Lightning", "01:00", 130.0f)};

std::vector<std::tuple<std::string, std::string, float>> ListViewItemsFactory::m_devices_outdoor =
{std::make_tuple("Incandescent Lightning", "01:00", 300.0f),
std::make_tuple("LED Lighning", "01:00", 100.0f), std::make_tuple("CFL Lightning", "01:00", 130.0f)};

std::vector<std::tuple<std::string, std::string, float>> ListViewItemsFactory::m_devices_other =
{std::make_tuple("Electric Cooker", "00:30", 2700.0f), std::make_tuple("Microwave", "00:05", 2000.0f),
std::make_tuple("Kettle", "00:15", 600.0f), std::make_tuple("name", "00:10", 100.0f),
std::make_tuple("name", "00:10", 100.0f), std::make_tuple("name", "00:10", 100.0f),
std::make_tuple("name", "00:10", 100.0f), std::make_tuple("name", "00:10", 100.0f),
std::make_tuple("name", "00:10", 100.0f), std::make_tuple("name", "00:10", 100.0f)};

//std::shared_ptr<ListViewItem> ListViewItemsFactory::buildKitchenListViewItem() {
//  sf::Text text;
//  std::string name("Kitchen");
//  auto root = std::make_shared<ListViewItem>(ResourceHolder::getInstance().getSprite(0), text, name);
//
//  auto Factory = [&root](std::vector<std::tuple<std::string, float, float>> items) {
//    int offset = 0;
//    for (auto item : items) {
//      auto child = ListViewItemsFactory::buildDeviceListViewItem(item);
//      child->setPosition(0.0f, 108.0f * offset);
//      root->appendChild(child);
//      offset++;
//    }
//  };
//
//  Factory(m_devices_kitchen);
//  Factory(m_devices_living_room);
//  Factory(m_devices_bathroom);
//  Factory(m_devices_other);
//  return root;
//}

std::shared_ptr<ListViewItem> ListViewItemsFactory::buildDeviceListViewItem(std::tuple<std::string, std::string, float>& item) {
  sf::Text text;
  auto device = std::make_shared<model::Device>(std::get<0>(item), std::get<2>(item), std::get<1>(item));
  auto child = std::make_shared<ListViewItem>(ResourceHolder::getInstance().getSprite(1), text, device);

  return child;
}

void ListViewItemsFactory::buildListViewStructure(ListView& listview) {

  sf::Text text;
  auto kitchen = std::make_shared<ListViewItem>(ResourceHolder::getInstance().getSprite(0), text, "Kitchen");
  auto living_room = std::make_shared<ListViewItem>(ResourceHolder::getInstance().getSprite(0), text, "Living Room");
  auto bedroom = std::make_shared<ListViewItem>(ResourceHolder::getInstance().getSprite(0), text, "Bedroom");
  auto bathroom = std::make_shared<ListViewItem>(ResourceHolder::getInstance().getSprite(0), text, "Bathroom");
  auto laundry_room = std::make_shared<ListViewItem>(ResourceHolder::getInstance().getSprite(0), text, "Laundry Room");
  auto outdoor = std::make_shared<ListViewItem>(ResourceHolder::getInstance().getSprite(0), text, "Outdoors");
  auto other = std::make_shared<ListViewItem>(ResourceHolder::getInstance().getSprite(0), text, "Other");

  auto Factory = [&](std::shared_ptr<ListViewItem> root, std::vector<std::tuple<std::string, std::string, float>> items) {
    int offset = 0;
    for (auto item : items) {
      auto child = ListViewItemsFactory::buildDeviceListViewItem(item);
      child->setPosition(0.0f, 108.0f * offset);
      root->appendChild(child);
      offset++;
    }
  };

  Factory(kitchen, m_devices_kitchen);
  kitchen->setPosition(0.0f, 0.0f);
  Factory(living_room, m_devices_living_room);
  living_room->setPosition(0.0f, 110.0f);
  Factory(bathroom, m_devices_bathroom);
  bathroom->setPosition(0.0f, 220.0f);
  Factory(bedroom, m_devices_bedroom);
  bedroom->setPosition(0.0f, 330.0f);
  Factory(laundry_room, m_devices_laundry_room);
  laundry_room->setPosition(0.0f, 440.0f);
  Factory(outdoor, m_devices_outdoor);
  outdoor->setPosition(0.0f, 550.0f);
  Factory(other, m_devices_other);
  other->setPosition(0.0f, 660.0f);

  listview.insert(kitchen);
  listview.insert(living_room);
  listview.insert(bedroom);
  listview.insert(bathroom);
  listview.insert(laundry_room);
  listview.insert(outdoor);
  listview.insert(other);
}
} /* namespace GUI */
