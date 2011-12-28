#ifndef __PRINTBUFFER_H__
#define __PRINTBUFFER_H__

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct printbuffer {
	char **buffer;
	int block;
	int len;
	int cursor;

	void *(*pf_malloc)(size_t size);
	void (*pf_free)(void *ptr);
	void *(*pf_realloc)(void *ptr, size_t size);
};

struct printbuffer *printbuffer_mem_new(char **buffer, int block,
                                        void *(*pf_malloc)(size_t size),
                                        void (*pf_free)(void *ptr),
                                        void *(*pf_realloc)(void *ptr, size_t size));
struct printbuffer *printbuffer_bloc_new(char **buffer, int block);
struct printbuffer *printbuffer_new(char **buffer);
void print_buffer_augment(struct printbuffer *pf, int nbytes);
int printbuffer_vprintf(struct printbuffer *pf, const char *format, va_list ap);
int printbuffer_printf(struct printbuffer *pf, const char *format, ...);
void printbuffer_cat_len(struct printbuffer *pf, const char *str, int len);
void printbuffer_char(struct printbuffer *pf, char c);
void printbuffer_cat(struct printbuffer *pf, const char *str);

static inline
struct printbuffer *_printbuffer_mem_new(char **buffer, int block,
                                        void *(*pf_malloc)(size_t size),
                                        void (*pf_free)(void *ptr),
                                        void *(*pf_realloc)(void *ptr, size_t size))
{
	struct printbuffer *pf;

	pf = pf_malloc(sizeof(struct printbuffer));
	pf->buffer = buffer;
	pf->block = block;
	pf->pf_malloc = pf_malloc;
	pf->pf_realloc = pf_realloc;
	pf->pf_free = pf_free;
	pf->len = 0;
	pf->cursor = 0;

	*pf->buffer = NULL;

	return pf;
}

static inline
struct printbuffer *_printbuffer_bloc_new(char **buffer, int block)
{
	return _printbuffer_mem_new(buffer, block, malloc, free, realloc);
}

static inline
struct printbuffer *_printbuffer_new(char **buffer)
{
	return _printbuffer_mem_new(buffer, 1, malloc, free, realloc);
}

static inline
void _print_buffer_augment(struct printbuffer *pf, int nbytes)
{
	pf->len = ( (pf->cursor + nbytes) / pf->block ) * pf->block;
	*pf->buffer = pf->pf_realloc(*pf->buffer, pf->len);
}

static inline
int _printbuffer_vprintf(struct printbuffer *pf, const char *format, va_list ap)
{
	va_list ap2;
	int len;

	va_copy(ap2, ap);
	len = vsnprintf(&(*pf->buffer)[pf->cursor], pf->len - pf->cursor, format, ap);
	if (len >= pf->len - pf->cursor) {
		_print_buffer_augment(pf, len + 1);
		vsnprintf(&(*pf->buffer)[pf->cursor], pf->len - pf->cursor, format, ap2);
	}
	pf->cursor += len;
	
}

static inline
int _printbuffer_printf(struct printbuffer *pf, const char *format, ...)
{
	va_list ap;
	int ret;

	va_start(ap, format);
	ret = printbuffer_vprintf(pf, format, ap);
	va_end(ap);

	return ret;
}

static inline
void _printbuffer_cat_len(struct printbuffer *pf, const char *str, int len)
{
	if (pf->len - pf->cursor <= len)
		_print_buffer_augment(pf, len + 1);
	memcpy(&(*pf->buffer)[pf->cursor], str, len);
	pf->cursor += len;
	(*pf->buffer)[pf->cursor] = '\0';
}

static inline
void _printbuffer_char(struct printbuffer *pf, char c)
{
	if (pf->len - pf->cursor < 1)
		_print_buffer_augment(pf, 1);
	(*pf->buffer)[pf->cursor] = c;
	pf->cursor++;
}

static inline
void _printbuffer_cat(struct printbuffer *pf, const char *str)
{
	for (; *str != '\0'; str++)
		printbuffer_char(pf, *str);
	printbuffer_char(pf, '\0');
}


#endif /* __PRINTBUFFER_H__ */
