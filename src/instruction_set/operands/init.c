#include <operands.h>
#include "operand_types.h"
#include <instruction_types.h>

//void	_add_gp_reg_type(t_operand_set *set) {
//	t_operand_type	gp_reg = {
//		.type = GP_REG,
//		.is_type = _is_gp_reg,
//		.new_operand = _new_gp_reg,
//	};
//	dyn_arr_add_save((void**)&set->set, &gp_reg, set->count++);
//}

//t_operand_set	new_gp_reg_set(void) {
//	t_operand_type	gp_reg = {
//		.type = GP_REG,
//		.is_type = _is_gp_reg,
//		.new_operand = _new_gp_reg,
//	};
//}

static t_operand_type	_match_type(const t_operand_set set, char *operand_str) {
	t_operand_type	error = {.is_type = NULL, .new_operand = NULL,
		.type = OPERAND_ERROR,};
	for (size_t i = 0; i < set.count; i++) {
		if (set.set[i].is_type(operand_str)) {
			return (set.set[i]);
		}
	}
	for (size_t i = 0; i < set.sub_set_count; i++) {
		t_operand_type	ret = _match_type(set.sub_sets[i], operand_str);
		if (ret.type != OPERAND_ERROR) {
			return (ret);
		}
	}
	return (error);
}

//t_operand	new_operand(t_operand_set set, char *operand_str) {
//	t_operand_type	type = _match_type(set, operand_str);
//	assert(type.type != OPERAND_ERROR && "operand not in given opernd set");
//	return (type.new_operand(operand_str));
//}

//new_operand(instruct, instruct_parts[1], instruct_parts[2], operands);
void	new_operand(const t_instruct instruct, char *operand_str_left,
			char *operand_str_right, t_operand operands[2])
{

	t_operand_combination	cur_sets;
	t_operand_set			cur_set;
	t_operand_type			left_type;
	t_operand_type			right_type;

	for (size_t set_pair_idx = 0;
			set_pair_idx < instruct.operand_combination_count; set_pair_idx++)
	{
		left_type.type = OPERAND_ERROR;
		right_type.type = OPERAND_ERROR;
		cur_sets = instruct.operand_combinations[set_pair_idx];

		for (size_t left_set_idx = 0; left_set_idx < cur_sets.left_count; left_set_idx++)
		{
			cur_set = cur_sets.left[left_set_idx];
			left_type = _match_type(cur_set, operand_str_left);
			if (left_type.type != OPERAND_ERROR) {
				break ;
			}
		}
		for (size_t right_set_idx = 0; right_set_idx < cur_sets.right_count; right_set_idx++)
		{
			cur_set = cur_sets.right[right_set_idx];
			right_type =_match_type(cur_set, operand_str_right);
			if (right_type.type != OPERAND_ERROR) {
				break ;
			}
		}
		if (left_type.type != OPERAND_ERROR && right_type.type != OPERAND_ERROR) {
			operands[0] = left_type.new_operand(operand_str_left);
			operands[1] = right_type.new_operand(operand_str_right);
			return ;
		}
	}
	printf("operand left: %s, operand right: %s\n",
		operand_str_left, operand_str_right);
	assert(0 && "operands could not be matched");
}

//makes an empty set and gives it the given type
t_operand_set	new_operand_set(t_operand_set_type set_type) {
	t_operand_set	set = {
		.set = dyn_arr_init2(3, sizeof(t_operand_type), 0, free_operand_type),
		.set_type = set_type,
		.sub_set_count = 0,
		.sub_sets = dyn_arr_init2(3, sizeof(t_operand_set), 0, free_operand_set),
	};
	assert(set.set && "malloc fail");
	assert(set.sub_sets && "malloc fail");
	return (set);
}


void	operand_set_add_type(t_operand_set *set, t_operand_type type) {
	dyn_arr_add_save((void**)(&set->set), &type, set->count++);
}

void	operand_set_add_sub_set(t_operand_set *set, t_operand_type type) {
	dyn_arr_add_save((void**)(&set->set), &type, set->count++);
}

t_operand_set	set_operand_error(void) {
	t_operand_type	error_type = {.is_type = NULL, .new_operand = NULL,
		.type = OPERAND_ERROR,};
	t_operand_set	error_set = new_operand_set(SET_OPERAND_ERROR);
	operand_set_add_type(&error_set, error_type);
	return (error_set);
}

void	init_leaf_operand_sets(
			t_operand_set leaf_operand_sets[SET_OPERAND_COUNT])
{
	t_operand_set	*arr = leaf_operand_sets; //shorter name
	t_operand_set_type	cur_type = SET_OPERAND_COUNT - 1;

	leaf_operand_sets[SET_OPERAND_ERROR] = new_operand_set(SET_OPERAND_ERROR);
	while (cur_type != SET_OPERAND_ERROR) {
		switch (cur_type) {
			//case (SET_OPERAND_MASTER):
			case (SET_OPERAND_ERROR):
				arr[SET_OPERAND_ERROR] = set_operand_error();
				break ;
			case (SET_OPERAND_EMPTY):
				arr[SET_OPERAND_EMPTY] = set_operand_empty();
				break ;
			//case (SET_GP_REG):
			case (SET_GP_REG_1):
				arr[SET_GP_REG_1] = set_gp_reg1();
				break ;
			case (SET_GP_REG_2):
				arr[SET_GP_REG_2] = set_gp_reg2();
				break ;
			case (SET_GP_REG_4):
				arr[SET_GP_REG_4] = set_gp_reg4();
				break ;
			case (SET_GP_REG_8):
				arr[SET_GP_REG_8] = set_gp_reg8();
				break ;
			case (SET_OPERAND_COUNT):
				assert(0 && "logic error: case shouldn't happen");
		}
		cur_type--;
	}
}

//returns 2 empty combinations
t_operand_combination	new_operand_combination(void) {
	t_operand_combination	combi = {
		.left_count = 0,
		.right_count = 0,
		.left = dyn_arr_init2(3, sizeof(t_operand_set), 0, NULL),
		.right = dyn_arr_init2(3, sizeof(t_operand_set), 0, NULL),
	};
	assert(combi.left && combi.right && "malloc fail");
	return (combi);
}

//add_set_to_combination takes pointers but does allocate copies itself
//the only reason it takes pointers is so there is a simply way to pass
//either a left/right or both sets
t_operand_combination	add_set_to_combination(t_operand_combination combi,
			const t_operand_set *add_left, const t_operand_set *add_right)
{
	if (add_left) {
		t_operand_set	left = *add_left;
		dyn_arr_add_save((void**)&combi.left, &left, combi.left_count++);
	}
	if (add_right) {
		t_operand_set	right = *add_right;
		dyn_arr_add_save((void**)&combi.right, &right,
			combi.right_count++);
	}
	return (combi);
}

void	add_operand_combination(t_instruct *instruct,
			t_operand_combination combi)
{
	dyn_arr_add_save((void**)&instruct->operand_combinations, &combi,
		instruct->operand_combination_count++);
}
