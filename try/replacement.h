#pragma once

#include "pagetable.h"

class Replacement {
protected:
    PageTable page_table;
    int num_page_faults;
    int num_page_replacements;

public:
    Replacement(int num_pages, int num_frames);
    virtual ~Replacement();

    virtual bool access_page(int page_num, bool is_write = false);
    virtual void touch_page(int page_num);
    virtual void load_page(int page_num);
    virtual int replace_page(int page_num) = 0;

    PageEntry getPageEntry(int page_num) {
        return page_table[page_num];
    }

    void print_statistics() const;
};