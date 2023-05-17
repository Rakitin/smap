#ifndef SMAP_H
#define SMAP_H

#ifdef __cplusplus
extern "C"
{
#endif
	
struct _smap;
typedef struct _smap t_smap;


t_smap* smap_create();
void smap_destroy(t_smap *p);

void smap_push(t_smap *p, const char *key, void* value);
void* smap_get(t_smap *p, const char *key);

void smap_clean(t_smap *p);

#ifdef __cplusplus
}
#endif

#endif
