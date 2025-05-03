#include "Inventory.h"

void Inventory::initialize()
{
    this->capasity = 10;
    this->nrOfWeapons = 0;
    this->weaponArray = new Weapon*[this->capasity];

    this->nullify();
}

void Inventory::expand()
{
}

void Inventory::nullify(const short from)
{
    for (size_t i = from; i < this->capasity; ++i)
    {
        this->weaponArray[i] = nullptr;
    }
}

void Inventory::freeMemory()
{
    for (size_t i = 0; i < this->capasity; ++i)
    {
        delete this->weaponArray[i];
    }
    delete[] this->weaponArray;
}

Inventory::Inventory()
{
}

Inventory::~Inventory()
{
}
