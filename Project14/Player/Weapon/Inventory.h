#ifndef INVENTORY_H
#define INVENTORY_H
#include "..//..//stdafx.h"
#include "Weapon.h"

class Inventory
{
private:
    Weapon** weaponArray;
    unsigned nrOfWeapons;
    unsigned capasity;

    void initialize();
    void expand();
    void nullify(const short from = 0);
    void freeMemory();
    
public:
    
    Inventory();
    virtual ~Inventory();
    
};
#endif