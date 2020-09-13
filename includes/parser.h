#ifndef PARSER_H
#define PARSER_H

typedef struct	s_parse
{
	t_obj		*obj;
	t_light		*light;
	int			obj_size;
	int			light_size;
	int			obj_index;
	int			light_index;
}				t_parse;


#endif
