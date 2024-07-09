#pragma once

#include "replacement.h"

class LIFOReplacement : public Replacement {
public:
    LIFOReplacement(int num_pages, int num_frames);
    ~LIFOReplacement();

    void load_page(int page_num) override;
    int replace_page(int page_num) override;
};
