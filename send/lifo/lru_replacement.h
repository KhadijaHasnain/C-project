#pragma once

#include <vector>
#include <list>
#include <unordered_map>

int simulate_LRU(const std::vector<int>& references, int num_frames) {
    std::unordered_map<int, bool> page_table;
    std::list<int> lru_list;

    int page_faults = 0;

    for (int page : references) {
        if (page_table.find(page) == page_table.end()) {
            if (lru_list.size() == num_frames) {
                int evicted_page = lru_list.front();
                lru_list.pop_front();
                page_table.erase(evicted_page);
            }
            lru_list.push_back(page);
            page_table[page] = true;
            ++page_faults;
        } else {
            // Page already in memory, move it to the back of the list (indicating recent use)
            lru_list.remove(page);
            lru_list.push_back(page);
        }
    }

    std::cout << "LRU Page Faults: " << page_faults << std::endl;
}
