#include "pagetable.h"

// Constructor
PageTable::PageTable(int numPages) : entries(numPages) {
    for (int i = 0; i < numPages; ++i) {
        entries[i].frameNumber = -1; 
        entries[i].validBit = false; 
        entries[i].dirtyBit = false; 
    }
}

// Destructor
PageTable::~PageTable() {
}
