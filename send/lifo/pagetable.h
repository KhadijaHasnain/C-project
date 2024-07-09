#ifndef PAGETABLE_H
#define PAGETABLE_H

#include <vector>
struct PageEntry {
    int frameNumber;
    bool validBit;
    bool dirtyBit; 
};

class PageTable {
private:
    std::vector<PageEntry> entries;

public:
    // Constructor
    PageTable(int numPages);

    // Getter for page table size
    int size() const;

    // Getter and setter for page entry
    PageEntry& operator[](int index);
};

#endif // PAGETABLE_H
