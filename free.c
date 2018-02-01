/*
** EPITECH PROJECT, 2021
** PSU_2017_malloc
** File description:
** Created by rectoria
*/

#include "malloc.h"

static void resize_heap()
{
	metadata_t *temp = allocated;

	while (temp->next && temp->next->next)
		temp = temp->next;
	if (temp->next && temp->next->occupied == 0) {
		brk(temp->next->ptr);
		temp->next = NULL;
	}
}

static void merge()
{
	metadata_t *temp = allocated;

	while (temp) {
		if (temp->next && temp->next->next && !temp->next->occupied &&
			!temp->next->next->occupied) {
			temp->size += HEADER + temp->next->size;
			temp->next = temp->next->next;
			continue ;
		}
		temp = temp->next;
	}
	resize_heap();
}

void free(void *ptr)
{
	metadata_t *temp = allocated;

	write(2, "free\n", 5);
	while (ptr && temp && temp->ptr != ptr)
		temp = temp->next;
	if (!temp || !ptr) {
		write(2, "endfree\n", 8);
		return ;
	}
	temp->occupied = 0;
	merge();
	write(2, "endfree\n", 8);
}
