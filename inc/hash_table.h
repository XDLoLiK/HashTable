/**
 * @defgroup   HASH_TABLE hash table
 *
 * @brief      This file implements hash table.
 *
 * @author     Stanislav
 * @date       2022
 */

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "list.h"

#include <time.h>

#define likely(x)   __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

struct hash_table {
    struct list **data;
    size_t size;
    size_t capacity;
};

// CD
struct hash_table *hash_table_new(size_t capacity);
struct hash_table *hash_table_delete(struct hash_table *ht);

// RU
size_t hash_table_size(struct hash_table const *ht);
struct list *hash_table_find(struct hash_table *ht, const char *key);
int hash_table_erase(struct hash_table *ht, const char *key);
int hash_table_insert(struct hash_table *ht, const char *key, const char *value);

// HASH
uint32_t murmurhash3_32 (const char *key, uint32_t len, uint32_t seed);

// EXTRA
int hash_table_print_contents(struct hash_table *ht);
int hash_table_print_histogram(struct hash_table *ht);

#endif // HASH_TABLE_H
