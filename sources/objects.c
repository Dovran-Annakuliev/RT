#include "../includes/objects.h"
#include <stdlib.h>
#include "../includes/sphere.h"
#include "../includes/plane.h"


t_obj			*new_obj_list(void		*object)
{
	t_obj		*list;
	if (!(list = (t_obj*)malloc(sizeof(t_obj))))
		return (NULL);
	if (!object)
	{
		list->next = NULL;
		list->content = NULL;
	}
	else
	{
		list->next = NULL;
		list->content = object;
	}
	return (list);
}

void			push_back(t_obj *head, void		*object)
{
	t_obj		*last;
	t_obj		*tmp;

	last = get_last_obj(head);
	tmp = new_obj_list(object);
	last->next = tmp;
}

t_obj			*get_last_obj(t_obj *head)
{
	if (head == NULL)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

int				pop(t_obj **head)
{
	t_obj	*prev;

	prev = NULL;
	if (head == NULL)
		return (0);
	prev = (*head);
	(*head) = (*head)->next;
	free(prev);
	return (1);
}

void			delete_obj_list(t_obj **head)
{
	while ((*head)->next) {
		pop(head);
		*head = (*head)->next;
	}
	free(*head);
}
