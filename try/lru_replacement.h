#pragma once

#include "replacement.h"

class LRUReplacement : public Replacement {
public:
    LRUReplacement(int num_pages, int num_frames);
    ~LRUReplacement();

    void touch_page(int page_num) override;
    void load_page(int page_num) override;
    int replace_page(int page_num) override;
};

