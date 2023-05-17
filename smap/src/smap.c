#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "smap.h"

struct t_pair
{
	char *key;
	void *value;
};

struct t_node
{
	struct t_pair pair;
	struct t_node *next;
};

typedef size_t (* t_hfunc)(const char *key);

struct _smap
{
	struct t_node **data;
	
	size_t capacity;
	size_t size;
	size_t count;
	size_t deepth;

	t_hfunc hash_func;
};

static size_t get_hash(const char *key)
{
	size_t hash = 0;
	while (*key) {
		hash += (size_t)*key;
		++key;
	}
	return hash;
}

// static size_t get_hash(const char *key)
// {
// 	size_t hash = 5381;
// 	while (*key++) {
// 		hash = ((hash << 5) + hash) + (size_t)*key;
// 	}
// 	return hash;
// }

#define CAPACITY 10

t_smap* smap_create()
{
	t_smap *p = calloc(1, sizeof *p);
	p->capacity = CAPACITY;
	p->data = calloc(p->capacity, sizeof *p->data);
	p->hash_func = get_hash;
	
	return p;
}

void smap_destroy(t_smap *p)
{
	size_t idx;
	for (idx = 0; idx < p->capacity; ++idx) {
		if (!p->data[idx]) {
			continue;
		}
		struct t_node *cur = p->data[idx];
		while (cur) {
			struct t_node *next = cur->next; 
			free(cur->pair.key);
			free(cur->pair.value);
			free(cur);
			cur = next;
		}
	}
	free(p->data);
	free(p);
}

static void rebuild(t_smap *p)
{
	size_t capacity = p->capacity + (p->capacity / 2);
	struct t_node **data = calloc(capacity, sizeof *data);
	size_t count = 0;
	size_t deepth = 0;
	size_t size = 0;

	size_t idx;
	for (idx = 0; idx < p->capacity; ++idx) {
		if (!p->data[idx]) {
			continue;
		}
		struct t_node *cur = p->data[idx];
		while (cur) {
			struct t_node *next = cur->next; 
			size_t idx = get_hash(cur->pair.key)%capacity;
			if (!data[idx]) {
				data[idx] = calloc(1, sizeof *data[idx]);
				data[idx]->pair = cur->pair;
				++count;
				++size;
				deepth = (deepth < 1) ? 1 : deepth;
			}
			else {
				struct t_node *item = data[idx];
				struct t_node *prev;
				size_t d = 0;
				while (item) {
					prev = item;
					item = item->next;
					++d;
					deepth = (deepth < d) ? d : deepth;
				}
				prev->next = calloc(1, sizeof *prev->next);
				prev->next->pair = cur->pair;
				++count;
			}
			free(cur);
			cur = next;
		}
	}
	free(p->data);

	p->capacity = capacity;
	p->data = data;
	p->size = size;
	p->count = count;
	p->deepth = deepth;
}

void smap_push(t_smap *p, const char *key, void *value)
{
	size_t idx = p->hash_func(key)%p->capacity;
	if (!p->data[idx]) {
		p->data[idx] = calloc(1, sizeof *p->data[idx]);
		p->data[idx]->pair.key = strdup(key);
		p->data[idx]->pair.value = value;
		++p->count;
		++p->size;
		p->deepth = (p->deepth < 1) ? 1 : p->deepth;
	}
	else {
		struct t_node *cur = p->data[idx];
		struct t_node *prev;
		size_t deepth = 0;
		while (cur) {
			if (!strcmp(cur->pair.key, key)) {
				free(cur->pair.value);
				cur->pair.value = value;
				return;
			}
			prev = cur;
			cur = cur->next;
			++deepth;
			p->deepth = (p->deepth < deepth) ? deepth : p->deepth;
		}
		prev->next = calloc(1, sizeof *prev->next);
		prev->next->pair.key = strdup(key);
		prev->next->pair.value = value;
		++p->count;
	}
	
	if ((double)p->size > (double)p->capacity * 0.75) {
		rebuild(p);
	}
}

void* smap_get(t_smap *p, const char *key)
{
	size_t idx = p->hash_func(key)%p->capacity;
	if (!p->data[idx]) {
		return NULL;
	}
	else {
		struct t_node *cur = p->data[idx];
		while (cur) {
			if (!strcmp(cur->pair.key, key)) {
				return cur->pair.value;
			}
			cur = cur->next;
		}
	}
	return NULL;
}

void smap_clean(t_smap *p)
{
	size_t idx;
	for (idx = 0; idx < p->capacity; ++idx) {
		if (!p->data[idx]) {
			continue;
		}
		struct t_node *cur = p->data[idx];
		while (cur) {
			struct t_node *next = cur->next; 
			free(cur->pair.key);
			free(cur->pair.value);
			free(cur);
			cur = next;
		}
	}
	free(p->data);
	p->capacity = CAPACITY;
	p->size = 0;
	p->data = calloc(p->capacity, sizeof *p->data);
}
