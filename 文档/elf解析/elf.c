#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <elf.h>
#include <unistd.h>

//elf文件头、section头表、program头表、Segment和Section映射表解析
int check_head(FILE *file )
{
		FILE *file_elf = file;
		int i = 0;
		int MagNum = 0;
		unsigned long  file_size = 0;
		int sechnum = 0;
		uint32_t symsize = 0;
		uint32_t symoff = 0;
		uint32_t nSyms = 0,kk=0;

		Elf64_Ehdr *Elf_header = calloc(1, sizeof(Elf64_Ehdr));
		//	Elf64_Sym  *Symbol_tab = calloc(1, sizeof(Elf64_Sym));

		fseek(file_elf,0,SEEK_END);
		file_size = ftell(file_elf);
		fseek(file_elf,0,SEEK_SET);
		//文件大小
		printf("file total size is:%ld bytes\n",file_size);
		fread(Elf_header,sizeof(Elf64_Ehdr),1,file_elf);	

		//确认是否为elf格式
		if((Elf_header->e_ident[0] == '\x7f') && (Elf_header->e_ident[1] == ELFMAG1) \
						&& (Elf_header->e_ident[2] == ELFMAG2) && (Elf_header->e_ident[3] == ELFMAG3))
		{	
				printf("This is ELF file!\n");
		}
		else
		{
				printf("NOT ELF file!\n");
				return -1;
		}
		//判断elf头是否正确
		if(Elf_header->e_ehsize != sizeof(*Elf_header))
		{
				printf("ELF file header size is err\n!");
				return -1;
		}
		if(Elf_header->e_type != ET_REL && Elf_header->e_type != ET_EXEC )
		{
				printf("file type is err!__FUNCTION__ %s __LINE__ %d\n",__FUNCTION__,__LINE__);
		}
		//1.ELF header解析
		printf("\n");
		printf("Magic:\t");
		for(MagNum=0; MagNum<16; MagNum++)
		{
				printf("%02x ",Elf_header->e_ident[MagNum]);
		}

		printf("\n");
		printf("Type(类型):---------------------------------------------%d\n",Elf_header->e_type);
		printf("Machine(系统架构):--------------------------------------%d\n",Elf_header->e_machine);
		printf("Version(版本):------------------------------------------%#02x\n",Elf_header->e_version);
		printf("Entry point address(入口地址):--------------------------%#02x\n",Elf_header->e_entry);
		printf("Start of program headers(程序头起点):-------------------%d(bytes)\n",Elf_header->e_phoff);
		printf("Start of section headers(section头起点):----------------%d(bytes)\n",Elf_header->e_shoff);
		printf("Flags(标志):--------------------------------------------%#02x\n",Elf_header->e_flags);
		printf("Size of this header(本头大小):--------------------------%d(bytes)\n",Elf_header->e_ehsize);
		printf("Size of program headers(程序头大小):--------------------%d(bytes)\n",Elf_header->e_phentsize);
		printf("Number of program headers(程序头个数):------------------%d\n",Elf_header->e_phnum);
		printf("Size of section headers(section头大小):-----------------%d(bytes)\n",Elf_header->e_shentsize);
		printf("Number of section headers(section头个数):---------------%d\n",Elf_header->e_shnum);
		printf("Section header string table index(section头表索引):-----%d\n",Elf_header->e_shstrndx);

		//2.section header解析
		sechnum = Elf_header->e_shnum;
		Elf64_Shdr *Section_headerD = calloc(sechnum, sizeof(Elf64_Shdr));
		Elf64_Shdr *Section_header = Section_headerD;
		fseek(file_elf,Elf_header->e_shoff,SEEK_SET);
		printf("\n/*****section header table****/\n");
		fread(Section_header,sizeof(Elf64_Shdr),sechnum,file_elf);
		printf("[Nr] Name          Type          Addr         Off      Size     ES Flg  Al");
		Elf64_Addr sectionAddr[64];
		for(i=0; i<sechnum; i++)
		{
				printf("\n[%d]  %x              %2x            %08x     %06x    %06x   %02x %02x  %02x "\
								, i,Section_header->sh_name,Section_header->sh_type,Section_header->sh_addr,\
								Section_header->sh_offset,Section_header->sh_size,Section_header->sh_entsize,\
								Section_header->sh_flags,Section_header->sh_addralign);
				sectionAddr[i] = Section_header->sh_addr;
				Section_header++;
		}
		
		//3.Program Header解析
		uint32_t phoffset = Elf_header->e_phoff; //程序头表偏移
		uint16_t phnum = Elf_header->e_phnum;//程序头表数目
		uint16_t phentsize = Elf_header->e_phentsize;// 程序头表大小
		int num = 0;
		Elf64_Phdr *Pro_headerD = calloc(phnum, phentsize);
		Elf64_Phdr *Pro_header = Pro_headerD;
		fseek(file_elf,phoffset,SEEK_SET);
		fread(Pro_header,phentsize,phnum,file_elf);
		printf("\n");
		printf("\n/*****Program Headers:*****/\n");
		printf("starting at offset: %d\n",phoffset);
		printf("Number of program headers: %d\n",phnum);
printf("Type           Offset   VirtAddr   PhysAddr   FileSiz     MemSiz    Flg\n");
		for(num=0; num<phnum; num++)
		{
				printf("%d           %-#6x   %-#x   %-#x   %-#5x     %-#5x    %-#x\n",\
								Pro_header->p_type,Pro_header->p_offset,Pro_header->p_vaddr,Pro_header->p_paddr,\
								Pro_header->p_filesz,Pro_header->p_memsz,Pro_header->p_flags);
				Pro_header++;
		}

		Pro_header = Pro_headerD;
		Section_header = Section_headerD;
		Elf64_Word section_name;
		printf("\n/*****Segment->Sections:*****/\n");
		printf("Segment               Sections\n");
		for(num=0; num<phnum; num++)
		{

				printf("%d   ----->   ", num);

				for(i=0; i<sechnum; i++)
				{
						if(sectionAddr[i] >= Pro_header->p_vaddr && sectionAddr[i] < Pro_header->p_vaddr + Pro_header->p_memsz)
						{
								section_name = (Section_header + i)->sh_name;
								printf("%x ", section_name);
						}
				}
				printf("\n");
				Pro_header++;
		}



		//释放内存
		free(Elf_header);
		Elf_header = NULL;
		free(Section_headerD);
		Section_headerD = NULL;
		free(Pro_headerD);
		Pro_headerD = NULL;
		return 0;
}

int main(int argc, char * argv[])
{
		char *path = argv[1];
		FILE *file_elf = NULL;
		file_elf = fopen(path,"rb");
		if(file_elf == NULL)
		{
				printf("open file err!!\n");
				return -1;
		}
		check_head(file_elf);
		fclose(file_elf);
		return 0;
}

