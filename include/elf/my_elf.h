#pragma once

#include <elf.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <libft.h>

typedef enum {
	SECTION_ERROR,
	SECTION_SHSTRTAB,
	SECTION_TEXT,
	SECTION_DATA,
	SECTION_BSS,
	SECTION_UNDEFINED,
	//SECTION_DEBUG,//todo: later, read: DWARF
	SECTION_COUNT,
}	t_section_type;

typedef struct {
	t_section_type	type;
	union {
		Elf64_Shdr		header;
		struct {
			/*from elf.h: */
			Elf64_Word	sh_name;		/* Section name (string tbl index) */
			Elf64_Word	sh_type;		/* Section type */
			Elf64_Xword	sh_flags;		/* Section flags */
			Elf64_Addr	sh_addr;		/* Section virtual addr at execution */
			Elf64_Off	sh_offset;		/* Section file offset */
			Elf64_Xword	sh_size;		/* Section size in bytes */
			Elf64_Word	sh_link;		/* Link to another section */
			Elf64_Word	sh_info;		/* Additional section information */
			Elf64_Xword	sh_addralign;		/* Section alignment */
			Elf64_Xword	sh_entsize;		/* Entry size if section holds table */
		};
	};
	uint8_t			*buf;//for binary data that will be output in the end
}	t_section;

//map with <key: string>, <value:t_symbol>
//todo t_str_map
typedef char*	t_str_map;
typedef t_str_map	t_symbol_tabel;

typedef struct {
	t_section		*arr;//dyn arr
	size_t			section_count;
	t_symbol_tabel	sybol_tabel;
}	t_sections;

typedef enum {
	SYMBOL_FUCTION,
	SYMBOL_LABEL,
	SYMBOL_VARIABLE,
}	t_symbol_type;

typedef struct {
	t_symbol_type	type;
	t_section		*section;
	char			*key;
	size_t			alignment_override;
	size_t			offset;
	size_t			size;
}	t_symbol;

// returns the symbol and if dest with a large enough size is given writes it to
// dest
t_symbol	get_symbol(char *key, uint8_t *dest, size_t dest_size);//todo

t_section	new_section(void);//todo
void		free_section(t_section *section);//todo

t_sections	init_sectios(void);//todo
void		free_sections(t_sections *sections);//todo
void		add_section_to_sections(t_sections *sections, t_section section);//todo

void		write_sect(t_section *section, uint8_t *data, size_t custom_alignment,
				size_t len);

