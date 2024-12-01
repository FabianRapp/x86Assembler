#include <my_elf.h>

//https://refspecs.linuxfoundation.org/elf/gabi4+/ch4.eheader.html

Elf64_Ehdr	get_basic_elf(void) {
	Elf64_Ehdr	header = {
		//todo: read https://refspecs.linuxfoundation.org/elf/gabi4+/ch4.eheader.html#elfid
		//* e_ident: Magic number and other info */
		.e_ident[EI_MAG0] = ELFMAG0,
		.e_ident[EI_MAG1] = ELFMAG1,
		.e_ident[EI_MAG2] = ELFMAG2,
		.e_ident[EI_MAG3] = ELFMAG3,
		.e_ident[EI_CLASS] = ELFCLASS64,
		.e_ident[EI_DATA] = ELFDATA2LSB,//little endian
		.e_ident[EI_VERSION] = EV_CURRENT,
		.e_ident[EI_OSABI] = ELFOSABI_LINUX,
		.e_ident[EI_ABIVERSION] = 0,
		.e_ident[EI_PAD] = 0,
		.e_ident[EI_PAD + 1] = 0,
		.e_ident[EI_PAD + 2] = 0,
		.e_ident[EI_PAD + 3] = 0,
		.e_ident[EI_PAD + 4] = 0,
		.e_ident[EI_PAD + 5] = 0,
		.e_ident[EI_PAD + 6] = 0,
		.e_type =  ET_NONE,/* file type */
		.e_machine = EM_X86_64,		/* Architecture */
		.e_version = 1,		/* Object file version */
		.e_entry = 0,		/* Entry point virtual address */
		.e_phoff = 0,		/* program header table's file offset in bytes */
		.e_shoff = 0,		/* Section header table file offset in bytes*/
		.e_flags = 0,		/* Processor-specific flags */
		.e_ehsize = sizeof(Elf64_Ehdr),	/* ELF header size in bytes */
		.e_phentsize = sizeof(Elf64_Half),	/* Program header table entry size */
		.e_phnum = 14,		/* Program header table entry count */
		/* todo:
		read:
			https://refspecs.linuxfoundation.org/elf/gabi4+/ch4.sheader.html
			https://refspecs.linuxfoundation.org/elf/gabi4+/ch4.strtab.html
		*/
		.e_shentsize = 0,//todo		/* Section header table entry size */
		.e_shnum = 0, //todo		/* Section header table entry count */
		.e_shstrndx = SHN_UNDEF, //todo	/* Section header string table index */

	};
	assert(header.e_ehsize == header.e_phentsize * header.e_phnum
		&& "header sizes are off");
	assert(!strncmp((char *)&header, ELFMAG, SELFMAG)
		&& "first magic elf header bytes are off");
	return (header);
}

void	make_executable_elf(Elf64_Ehdr *header) {
	header->e_type = ET_EXEC;
	header->e_entry = 0;
}
