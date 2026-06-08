#include "Market.h"
#include "GameException.h"

Market::Market()
{
    catalog = {
        {ProductType::WheatSeed, 20, 10},
        {ProductType::CornSeed,  20, 15},
        {ProductType::Chicken,   10, 25},
        {ProductType::Cow,        5, 50},
        {ProductType::Wheat,     20, 15},
        {ProductType::Corn,      20, 20},
        {ProductType::Egg,       15, 30},
        {ProductType::Milk,      10, 60}
    };
}

void Market::showCatalog() const
{
    
    for (const auto& item : catalog) {
        std::println("id:{} product:{} qty:{} price:{}",
            item.getId(),
            Utils::productTypeToString(item.getProduct()),
            item.getQuantity(),
            item.getPrice());
    }
}

MarketItem* Market::findItem(unsigned int id)
{
    auto it = std::find_if(catalog.begin(), catalog.end(), [&id](const MarketItem& item) {
        return id == item.getId();
        });

    return it != catalog.end() ? &(*it) : nullptr;
}

bool Market::buyItem(unsigned int id, unsigned int quantity, unsigned int& playerBalance, Barn& barn)
{
    MarketItem* item = findItem(id);

    if (!item) {
        std::println ("Product does not exist!");
        return false;
    }

    if (item->getQuantity() < quantity) {
        std::println ("Not enough quantity on the market!");
        return false;
    }

    unsigned int totalPrice = item->getPrice()* quantity;
    if (playerBalance < totalPrice) {
        std::println ("Not enough balance!");
        return false;
    }

    item->setQuantity(item->getQuantity() - quantity);
    playerBalance -= totalPrice;
    barn.addProduct(item->getProduct(), quantity);

    std::println("Purchase was successful!");

    return true;
}

bool Market::sellItem(unsigned int id, unsigned int quantity, unsigned int& playerBalance, Barn& barn)
{
    MarketItem* item = findItem(id);


    if (!item) {
        std::println("Product does not exist!");
        return false;
    }

    if (barn.getQuantity(item->getProduct()) < quantity) {
        std::println ("Not enough quantity in barn!");
        return false;
    }

    barn.removeProduct(item->getProduct(), quantity);
    item->setQuantity(item->getQuantity() + quantity);
    playerBalance += item->getPrice() * quantity;

    std::println("The sale was successful!");

    return true;
}

void Market::restock(unsigned int id, unsigned int quantity)
{
    MarketItem* item = findItem(id);

    if (!item) return;

    item->setQuantity(item->getQuantity() + quantity);
}

void Market::changePrice(unsigned int id, unsigned int newPrice)
{
    MarketItem* item = findItem(id);

    if (!item) return;

    item->setPrice(newPrice);
}

std::ostream& operator<<(std::ostream& os, const Market& market)
{
    os << "MARKET " << market.catalog.size() << "\n";

    for (const auto& item : market.catalog) {
        os << item << "\n";
    }

    return os;
}

std::istream& operator>>(std::istream& is, Market& market)
{
    std::string section;
    unsigned int count;
    is >> section >> count;

    if (section != "MARKET")
        throw InvalidFileFormatException();

    market.catalog.clear();

    for (unsigned int i = 0; i < count && is; i++) {
        MarketItem item;
        if (is >> item)
            market.catalog.push_back(item);
    }
    return is;
}
