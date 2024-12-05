#include <my_elf.h>

//untested
void	write_sect(t_section *section, uint8_t *data, size_t custom_alignment,
	size_t len)
{
	size_t	alignment = custom_alignment != 0
		? custom_alignment : section->sh_addralign;
	while (section->sh_size % alignment) {
		section->sh_size++;
	}
	while (len--) {
		dyn_arr_add_save((void **)&section->buf, data++, section->sh_size++);
	}
}
