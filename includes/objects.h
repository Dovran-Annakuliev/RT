#ifndef OBJECTS_H
#define OBJECTS_H

typedef struct			s_obj
{
	void				*content;
	int					type;
	struct s_obj		*next;
}				t_obj;

t_obj			*new_obj_list(void		*object, int type);
void			push_back(t_obj *head, void		*object, int type);
t_obj			*get_last_obj(t_obj *head);
int				pop(t_obj **head);
void			delete_obj_list(t_obj **head);

#endif
