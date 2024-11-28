#ifndef OPERAND_H
#define OPERAND_H

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <instruction_types.h>

#ifndef UNKNOWN_SIZE
# define UNKNOWN_SIZE -1
#endif // UNKNOWN_SIZE

t_operand	new_operand(t_operand_type type);


#endif //OPERAND_H
