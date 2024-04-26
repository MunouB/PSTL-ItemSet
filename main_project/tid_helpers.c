#include "main.h"
#include <assert.h>

tid_map *init_tid_map(int initial_capacity) {
    tid_map *map = malloc(sizeof(tid_map));
    map->entries = malloc(sizeof(tid_entry) * initial_capacity);
    map->count = 0;
    map->capacity = initial_capacity;
    return map;
}

void add_to_tid_map(tid_map *map, int tid, item_set *set) {
    // Resize the array if needed
    if (map->count == map->capacity) {
        map->capacity *= 2;
        map->entries = realloc(map->entries, sizeof(tid_entry) * map->capacity);
    }

    map->entries[map->count].tid = tid;
    map->entries[map->count].itemset = cpy_item_set(set);
    map->count++;
}

void free_tid_map(tid_map *map) {
    for (int i = 0; i < map->count; i++) {
        free(map->entries[i].itemset->items);
        free(map->entries[i].itemset);
    }
    free(map->entries);
    free(map);
}

bool all_items_of_tid_in_itemset(tid_map *map, int tid, item_set *set) {
    for (int i = 0; i < map->count; i++) {
        if (map->entries[i].tid == tid) {
            for (int j = 0; j < set->k; j++) {
                if (!item_in_item_set(set->items[j], map->entries[i].itemset)) {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}



void update_tid_sets(tid_map *map, hash_table *lk, baskets *bs) {
    assert(map != NULL);
    assert(lk != NULL);
    assert(bs != NULL);
    assert(bs->basket != NULL); // Ensure the basket array is not NULL

    // Reset map to have zero entries but keep the allocated memory for reuse
    map->count = 0;

    // For each basket, check which itemsets in lk it contains
    for (int i = 0; i < bs->count; i++) {
        assert(bs->basket[i] != NULL); // Ensure the individual basket is not NULL
        for (int j = 0; j < TABLE_SIZE; j++) {
            assert(lk->pointers != NULL); // Ensure the pointers array is not NULL
            hash_node *node = lk->pointers[j];
            while (node != NULL) {
                assert(node->item_set != NULL); // Ensure the item set in the node is not NULL
                if (all_items_of_set_in_bitmap(node->item_set, bs->basket[i], lk)) {
                    add_to_tid_map(map, i, node->item_set);
                }
                node = node->next;
            }
        }
    }
}

hash_table *generate_lk_from_tid_map(tid_map *map, int support) {
    hash_table *new_lk = init_hash_table();
    for (int i = 0; i < map->count; i++) {
        tid_entry entry = map->entries[i];
        
        if (entry.itemset->count >= support) {
            // Add it to the new Lk
            add_item_set_to_hash_table(entry.itemset, new_lk);
        }
    }
    return new_lk;
}
