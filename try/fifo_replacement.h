#pragma once

#include "replacement.h"

class FIFOReplacement : public Replacement {
public:
    FIFOReplacement(int num_pages, int num_frames);
    ~FIFOReplacement();

    void load_page(int page_num) override;
    int replace_page(int page_num) override;
};
