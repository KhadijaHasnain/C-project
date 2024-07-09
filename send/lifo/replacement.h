#ifndef REPLACEMENT_H
#define REPLACEMENT_H

#include "pagetable.h"

class Replacement {
protected:
    int numPageFaults;
    int numPageReplacements;
    PageTable page_table;

public:
    Replacement(int num_pages, int num_frames);
    virtual ~Replacement();

    virtual bool access_page(int page_num, bool is_write = false) = 0;
    virtual void touch_page(int page_num) {}
    virtual void load_page(int page_num) {}
    virtual int replace_page(int page_num) = 0;
    PageEntry getPageEntry(int page_num) const;
    void print_statistics() const;

    int getPageFaults() const;
    int getPageReplacements() const;
};

#endif // REPLACEMENT_H
