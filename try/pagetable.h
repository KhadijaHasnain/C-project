#pragma once

#include <vector>

class PageEntry {
public:
    int frame_num;
    bool valid = false;
    bool dirty = false;
};

class PageTable {
private:
    std::vector<PageEntry> pages;

public:
    PageTable(int num_pages);
    ~PageTable();

    PageEntry& operator[](int i) {
        return pages[i];
    }
};
