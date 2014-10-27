/*******************************
 * tiankai
 * 2014 2 22
 * commit 3.10号
 *
 *
 *
 * **********************************/

#include <elf.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <dlfcn.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <elf.h>

#define MAX_SIZE 100000000

#define str_LENGTH 52 //elf 文件的头部的长度
char *section_name;

#define unsiged int

char tmp[MAX_SIZE];

Elf32_Ehdr elf_header;
Elf32_Shdr elf_shdr;

/*******
 * defination every seciton's off
 *
 *
 * *********/
Elf32_Off elf_bss_off = 0;
Elf32_Off elf_comment_off= 0;
Elf32_Off elf_data_off= 0;
Elf32_Off elf_data1_off= 0;
Elf32_Off elf_debug_off= 0;
Elf32_Off elf_dynamic_off= 0;
Elf32_Off elf_dynstr_off= 0;
Elf32_Off elf_dynsym_off= 0;
Elf32_Off elf_fini_off= 0;
Elf32_Off elf_got_off= 0;
Elf32_Off elf_init_off= 0;
Elf32_Off elf_interp_off= 0;
Elf32_Off elf_line_off= 0;
Elf32_Off elf_note_off= 0;
Elf32_Off elf_plt_off;
Elf32_Off elf_relname_off;
Elf32_Off elf_relaname_off;
Elf32_Off elf_rodata_off;
Elf32_Off elf_rodata1_off;
Elf32_Off elf_shstrtab_off;
Elf32_Off elf_strtab_off;
Elf32_Off elf_symtab_off;
Elf32_Off elf_text_off;
Elf32_Off elf_rel_dyn_off;
Elf32_Off elf_rel_plt_off;




Elf32_Word elf_rel_dyn_size;
Elf32_Word elf_rel_plt_size;
Elf32_Word elf_symtab_size;
Elf32_Word elf_dynamic_size;
Elf32_Word elf_dynsym_size;
Elf32_Word elf_got_size;


Elf32_Word elf_rel_dyn_info ;
Elf32_Word elf_rel_dyn_link;

Elf32_Word elf_rel_plt_info;
Elf32_Word elf_rel_plt_link;


/********************
 *function:read the file's elf header
 *
 *
 *
 *
 *
 * *************************/
void read_elf_header(const char * filename) {


	unsigned char str[str_LENGTH];

	int fd;
	fd = open(filename, O_RDONLY);
	if (-1 == fd) {
		printf("open the file failed!\n");
		return;
	}
	read(fd, str, str_LENGTH * sizeof(unsigned char));
	int i = 0;

	/***printf the elf header**/
	printf("ELF Header:\n");
	printf("Magic:  ");
	while (i < 16) {
		printf("%x ", str[i]);
		i++;
	}

	printf("\nClasss :\t\t");
	if ((str[0] == 0x7f) && (str[1] == 'E') && (str[2] == 'L')
			&& (str[3] == 'F')) {
		switch (str[4]) {
		case 0:
			printf("invalid file\n");
			break;
		case 1:
			printf("ELF 32\n");
			break;
		case 2:
			printf("ELF 64\n");
			break;
		}
	} else {
		printf("the file is not ELF! ");
		return;
	}

	printf("Endian:");
	switch (str[5]) {
	case 0:
		printf("invalid data\n");
		break;
	case 1:
		printf("little endian\n");
		break;
	case 2:
		printf("big endian \n");
		break;
	}

	printf("file version:\t\t %d \n", str[6]);

	/**printf the type ****/
	printf("Type ");
	elf_header.e_type = *(Elf32_Half *)&str[16];
	switch (elf_header.e_type) {
	case 0:
		printf("unknown file formate!\n");
		break;
	case 1:
		printf("relocateble file type!\n");
		break;
	case 2:
		printf("executable file type!\n");
		break;
	case 3:
		printf("shared objective file type!\n");
		break;
	case 4:
		printf("core file type!\n");
		break;
	default:
		break;

	}

	/****	printf the macchine****/
	printf("machine :\t\t");
	elf_header.e_machine = *(Elf32_Half *)&str[18];
	switch(elf_header.e_machine){
	case 0:
		printf("validate\n");
		break;
	case 1:
		printf("AT&T WE 32100\n");
		break;
	case 2:
		printf("SPARC\n");
		break;
	case 3:
		printf("Intel 80386\n");
		break;
	case 4:
		printf("Motorola 68000\n");
		break;
	case 5:
		printf("Motorala 88000\n");
		break;
	case 7:
		printf("Intel 80860\n");
		break;
	case 8:
		printf("MIPS RS3000\n");
		break;
	case 40:
		printf("ARM\n");
		break;
	}
	/**printt versison**/

	 elf_header.e_version = *(Elf32_Word *)&str[20];
	 printf("target file version : \t\t");
	 switch(elf_header.e_version)
	 {
	           case 0:
	                printf("Invalid Elf version\n");
	                break;
	           case 1:
	                printf("current version\n");
	                break;
	           default:
	                break;
	   }
	 /****printf e_entry*****/
	 elf_header.e_entry = *(Elf32_Addr *)&str[24];
	 printf("Entry point address(程序入口虚拟地址) : %p\n",(void *)elf_header.e_entry);

	 /*****printf phoff*********/
	 elf_header.e_phoff = *(Elf32_Off *)&str[28];
	 printf("start of program header table(程序头部表的的偏移量) :%d \n",elf_header.e_phoff);
	 /********printf section header table******/
	 elf_header.e_shoff = *(Elf32_Off *)&str[32];
	 printf("start of section header table（节区头部表的偏移量） :%d \n",elf_header.e_shoff);

	 /***printf Flags****/
	 elf_header.e_flags = *(Elf32_Word *)&str[36];
	 printf("Flags :%x\n",elf_header.e_flags);

	 elf_header.e_ehsize =*(Elf32_Half *)&str[40];
	 printf("size of this header（ELF 头部的大小） ：%dB\n",elf_header.e_ehsize);

	 elf_header.e_phentsize = *(Elf32_Half *)&str[42];
	 printf("size of program header table（程序头部表的大小） :%dB\n",elf_header.e_phentsize);

	 elf_header.e_phnum = *(Elf32_Half *)&str[44];
	 printf("number of the program header table（程序头部表的数目） :%d\n",elf_header.e_phnum);

	 elf_header.e_shentsize = *(Elf32_Half *)&str[46];
	 printf("size of the section header table（节区头部表的大小） :%dB\n",elf_header.e_shentsize);

	 elf_header.e_shnum = *(Elf32_Half *)&str[48];
	 printf("number of the seciton header table（节区头部表的数目） :%d\n",elf_header.e_shnum);

	 elf_header.e_shstrndx = *(Elf32_Half *)&str[50];
	 printf("section header string table index（节区头部表与节区名称字符串的索引） %d\n",elf_header.e_shstrndx);
	printf("\n");
	close(fd);

}

/***************
 *copyright : tiankai
 *description: read the information of string tab
 *
 *
 *
 *
 *
 * *******************************/

char *read_shstrtab(Elf32_Word name)
{

	int section_num = elf_header.e_shstrndx;   //字符串节区索引


	int strtab_off = elf_header.e_shentsize * section_num;//27 *40


	int strtab_base = elf_header.e_shoff + strtab_off; //  是自己理解错了 ！

	int elf_s_sh_offset=*( (Elf32_Off *)&tmp[strtab_base  + 16]); //这个地方 有问题？？？


	section_name = (char *)&tmp[elf_s_sh_offset + name];
	}
/*
*copyright: tiankai
*function:	read the information of the section
*arguments: the file's name to read
*return :
*
*/
void read_elf_shdr(const char * filename)
{
	printf("\nSection Header info...\nSection tab at offset 0x%x",elf_header.e_shoff);
	printf("\n[Nr]\tName\t\tType\t\tAddr\t\tOff\t\tSize\tES Flg Lk Inf Al\n");
//	printf("section off %d\n",elf_header.e_shoff);

	int section_off = elf_header.e_shoff;

	int i = 0;
	for( ; i < elf_header.e_shnum;i++)
	{

		printf("[%-2d]",i);
		elf_shdr.sh_name = *(Elf32_Word *)&tmp[section_off + 4*0];
		elf_shdr.sh_type = *(Elf32_Word *)&tmp[section_off + 4*1];
		elf_shdr.sh_flags = *(Elf32_Word *)&tmp[section_off + 4*2];
		elf_shdr.sh_addr = *(Elf32_Word *)&tmp[section_off + 4*3];
		elf_shdr.sh_offset = *(Elf32_Word *)&tmp[section_off + 4*4];
		elf_shdr.sh_size = *(Elf32_Word *)&tmp[section_off + 4*5];
		elf_shdr.sh_link = *(Elf32_Word *)&tmp[section_off + 4*6];
		elf_shdr.sh_info = *(Elf32_Word *)&tmp[section_off + 4*7];
		elf_shdr.sh_addralign = *(Elf32_Word *)&tmp[section_off + 4*8];
		elf_shdr.sh_entsize = *(Elf32_Word *)&tmp[section_off + 4*9];


		/********invoke the function read_shstrtab to get the str***********/

		section_name = read_shstrtab(elf_shdr.sh_name);

		printf("%-18s ",section_name);

/**  初始化 各个节区的偏移量**/
		if( strstr(section_name,".bss") !=0  )
		{
			elf_bss_off = elf_shdr.sh_offset;
		}
		if (strstr(section_name, ".comment") != 0)
		{
			elf_symtab_off = elf_shdr.sh_offset;
		}
		if (strstr(section_name, ".data") != 0)
		{
			elf_data_off = elf_shdr.sh_offset;
		}
		if (strstr(section_name, ".data1") != 0)
		{
			elf_data1_off = elf_shdr.sh_offset;
		}
		if (strstr(section_name, ".debug") != 0)
		{
			elf_debug_off = elf_shdr.sh_offset;
		}
		if (strstr(section_name, ".dynamic") != 0)
		{
			elf_dynamic_off = elf_shdr.sh_offset;
			elf_dynamic_size = elf_shdr.sh_size;// the size of the dynamic
		}

		if (strstr(section_name, ".dynstr") != 0)
		{
			elf_dynstr_off = elf_shdr.sh_offset;
		}
		if (strstr(section_name, ".dynsym") != 0)
		{
			elf_dynsym_off = elf_shdr.sh_offset;
			elf_dynsym_size = elf_shdr.sh_size;
		}
		if (strstr(section_name, ".fini") != 0)
		{
			elf_fini_off = elf_shdr.sh_offset;
		}
		if (strstr(section_name, ".got") != 0)
		{
			elf_got_off = elf_shdr.sh_offset;
			elf_got_size = elf_shdr.sh_size;
		}
		if (strstr(section_name, ".init") != 0)
		{
			elf_init_off = elf_shdr.sh_offset;
		}
		if (strstr(section_name, ".interp") != 0)
		{
			elf_interp_off = elf_shdr.sh_offset;
		}
		if (strstr(section_name, ".line") != 0)
		{
			elf_line_off = elf_shdr.sh_offset;
		}
		if (strstr(section_name, ".note") != 0)
		{
			elf_note_off = elf_shdr.sh_offset;
		}
		if (strstr(section_name, ".plt") != 0)
		{
			elf_plt_off = elf_shdr.sh_offset;
		}
		if (strstr(section_name, ".relname") != 0)
		{
			elf_relname_off = elf_shdr.sh_offset;
		}
		if (strstr(section_name, ".relaname") != 0)
		{
			elf_relaname_off = elf_shdr.sh_offset;
		}
		if (strstr(section_name, ".rodata") != 0)
		{
			elf_rodata_off = elf_shdr.sh_offset;
		}
		if (strstr(section_name, ".rodata1") != 0)
		{
			elf_rodata1_off = elf_shdr.sh_offset;
		}
		if (strstr(section_name, ".shstrtab") != 0)
		{
			elf_shstrtab_off = elf_shdr.sh_offset;
		}

		if (strstr(section_name,".strtab") != 0)
		{
			elf_strtab_off = elf_shdr.sh_offset;
		}

		if (strstr(section_name, ".symtab") != 0)
		{
			elf_symtab_off = elf_shdr.sh_offset;
			elf_symtab_size = elf_shdr.sh_size;   // the size of symtab
		}

		if (strstr(section_name, ".text") != 0)
		{
			elf_text_off = elf_shdr.sh_offset;
		}

		if (strstr(section_name, ".rel.dyn") != 0)
		{
			elf_rel_dyn_off = elf_shdr.sh_offset;
			elf_rel_dyn_size = elf_shdr.sh_size;
			elf_rel_dyn_info = elf_shdr.sh_info;
			elf_rel_dyn_link = elf_shdr.sh_link;

		}

		if (strstr(section_name, ".rel.plt") != 0)
		{
			elf_rel_plt_off = elf_shdr.sh_offset;
			elf_rel_plt_size = elf_shdr.sh_size;
			elf_rel_plt_info = elf_shdr.sh_info;
			elf_rel_plt_link = elf_shdr.sh_link;
		}




//		printf("section type:");
		switch(elf_shdr.sh_type)
					{
						case 0:{printf("%-10s"," NULL");					}break;
						case 1:{printf("%-10s"," PROGBITS");				}break;
						case 2:{printf("%-10s"," SYMTAB");					}break;
						case 3:{printf("%-10s"," STRTAB");					}break;
						case 4:{printf("%-10s"," RELA");					}break;
						case 5:{printf("%-10s"," HASH");					}break;
						case 6:{printf("%-10s"," DYNAMIC");					}break;
						case 7:{printf("%-10s"," NOTE");					}break;
						case 8:{printf("%-10s"," NOBITS");					}break;
						case 9:{printf("%-10s"," REL");						}break;
						case 10:{printf("%-10s"," UNDEF");					}break;
						case 11:{printf("%-10s"," DYNSYM");					}break;

						case 14:{printf("%-10s","INIT_ARRAY");              }break;
						case 15:{printf("%-10s","FINI_ARRAY");				}     break;
						case 16:{printf("%-10s","PREINIT_ARRAY");			}	  break;
						case 17:{printf("%-10s","GROUP");					}     break;
						case 18:{printf("%-10s","SYMTAB_SHNDX");			}     break;
						case 19:{printf("%-10s","NUM");						}     break;
						case 0x60000000:{printf("%-10s","");				}     break;
						case 0x6ffffff5:{printf("%-10s","");				}     break;
						case 0x6ffffff6:{printf("%-10s"," GNU_HASH");		}break;


						case 0x6fffffff:{printf("%-10s"," VERSYM");			}break;
						case 0X6ffffffe:{printf("%-10s"," VERNEED");		}break;
						case 0Xffffffa3:{printf("%-10s"," STRTAB");			}break;
						default:
						 printf("=====UDEF====\n");break;
					}

		printf("\t%08x",elf_shdr.sh_addr);
//
//		printf("section off :");
		printf("\t%8d",elf_shdr.sh_offset);

//		printf("section size :");
		printf("\t%6d",elf_shdr.sh_size);

//		printf("ES :");
		printf("\t%2d",elf_shdr.sh_entsize);

//		printf("Flag :");
		switch(elf_shdr.sh_flags){
		case 0:
			printf("");
			break;
		case 0x1:
			printf("%3s","W");
			break;
		case 0x2:
			printf("%3s","A");
			break;
		case 0x4:
			printf("%3s","E");
			break;
		case 0xf0000000:
			printf("%3s","M");
			break;
		case 0x3:
			printf("%3s","AW");
			break;
		case 0x5:
			printf("%3s","EW");
			break;
		case 0xf0000001:
			printf("%3s","MW");
			break;
		case 0x6:
			printf("%3s","AE");
			break;
		case 0xf0000002:
			printf("%3s","AM");
			break;
		case 0xf0000004:
			printf("%3s","EM");
			break;
		case 0x7:
			printf("%3s","AEW");
			break;
		case 0xf0000003:
			printf("%3s","AMW");
			break;
		case 0xf0000005:
			printf("%s3","EMW");
			break;
		case 0xf0000006:
			printf("%3s","AEM");
			break;
		case 0xf0000007:
			printf("%4s","AEMW");
			break;
		default:
			printf("UK");
			break;


		}
//		printf("Link :");
		printf(" %2x",elf_shdr.sh_link);

//		printf("Inf :");
		printf(" %2x",elf_shdr.sh_info);

//		printf("Al :");
		printf(" %2x",elf_shdr.sh_addralign);
		printf("\n");
		section_off += 40;
	}

	}

/****************************
 * function : read_elf_strtab
 *
 * description: relf_dyn.d_un.d_ptr = *(Elf32_Addr *) &tmp[elf_dynamic_off
											+ dynamic_off + 4];
			printf("\t\t0x%08x", elf_dyn.d_un.d_ptr);ead the infor mation of the string table
 *
 *
 *
 *
 *
 * ************************************/

char * read_elf_strtab(Elf32_Word name)
{


	return &tmp[elf_strtab_off + name];
}


/*********************************
 * function : read_elf_sym
 *
 * description : read the information of the symbol table
 *
 *
 *
 *
 *
 * ****************************************/


void read_elf_symtab()
{
	Elf32_Sym elf_sym;

	int symtab_off = 0;

	int symtab_num = (elf_symtab_size / sizeof(Elf32_Sym) );
	printf("Symbol table '.symtab' contains [%-2d] entries:\n",symtab_num);
	int i;

	printf("Num\tValue\t\tSize\tType\tBind\tother\tNdx\tName\n");
	for( i=0; i < symtab_num; i++)
	{
		elf_sym.st_name = *(Elf32_Word *) &tmp[elf_symtab_off + symtab_off + 0];
		elf_sym.st_value = *(Elf32_Addr *) &tmp[elf_symtab_off + symtab_off + 4];
		elf_sym.st_size = *(Elf32_Word *) &tmp[elf_symtab_off + symtab_off + 8];
		elf_sym.st_info = *(unsigned char *) &tmp[elf_symtab_off + symtab_off + 12];
		elf_sym.st_other = *(unsigned char *) &tmp[elf_symtab_off + symtab_off + 13];
		elf_sym.st_shndx = *(Elf32_Half *) &tmp[elf_symtab_off + symtab_off + 14];
		printf("[%2d]",i);

		printf("\t0x%08x",elf_sym.st_value);

		printf("\t%d",elf_sym.st_size);

		/**printf the information of type**/
		switch( (elf_sym.st_info) & 15)
		{
		case 0:printf("\t%s","NOTYPE");break;
		case 1:printf("\t%s","OBJECT");break;
		case 2:printf("\t%s","FUNC");break;
		case 3:printf("\t%s","SECTION");break;
		case 4:printf("\t%s","FILE");break;
		case 13:printf("\t%s","LOPROC");break;
		case 15:printf("\t%s","HIPROC");break;
		}

		/***print the information of Binding***/
		switch( (elf_sym.st_info>>4))
		{
		case 0:printf("\tLOCAL");break;
		case 1:printf("\tGLOBAL");break;
		case 2:printf("\tWEAK");break;
		case 13:printf("\tLOPROC");break;
		case 15:printf("\tHIPROC");break;
		default:printf("\tUNDFN");break;
		}

		printf("\t%-4d",elf_sym.st_other);


		/***printf the information of shndx**/
		switch(elf_sym.st_shndx)
		{
			case 0xfff1:printf("\t%-6s","ABS");break;
			case 0xfff2:printf("\t%-6s","COMMON");break;
			case 0:     printf("\t%-6s","UNDEF");break;
			default:printf("\t%d ",elf_sym.st_shndx);break;
		}

		char * symtab_name=read_elf_strtab(elf_sym.st_name);
		printf("\t%-8s",symtab_name);

		symtab_off +=16;// 递增的结构
		printf("\n");

	}
}

/*************
 * function : read_elf_rela
 *
 * description: read the information of relocation tab
 *????
 *
 * ***************/


/*****read the information of program header i******/
void read_elf_program_header()
{
	Elf32_Phdr elf_phdr;
	int pragram_off = 0;
	int i;
	printf("Program Header :\n");
	printf("Num\tType\tOffset\t\tvirtAddr\tPhysAddr\tFileSize\tMemSize\tFlag\t  Align\n");
	for(i = 0;i < elf_header.e_phnum;i++)
	{
		elf_phdr.p_type = *(Elf32_Word *)&tmp[elf_header.e_phoff + pragram_off + 4* 0];
		elf_phdr.p_offset = *(Elf32_Off  *)&tmp[elf_header.e_phoff + pragram_off + 4* 1];
		elf_phdr.p_vaddr = *(Elf32_Addr *)&tmp[elf_header.e_phoff + pragram_off + 4* 2];
		elf_phdr.p_paddr = *(Elf32_Addr *)&tmp[elf_header.e_phoff + pragram_off + 4* 3];
		elf_phdr.p_filesz = *(Elf32_Word *)&tmp[elf_header.e_phoff + pragram_off + 4* 4];
		elf_phdr.p_memsz = *(Elf32_Word *)&tmp[elf_header.e_phoff + pragram_off + 4* 5];
		elf_phdr.p_flags = *(Elf32_Word *)&tmp[elf_header.e_phoff + pragram_off + 4* 6];
		elf_phdr.p_align = *(Elf32_Word *)&tmp[elf_header.e_phoff + pragram_off + 4* 7];

		printf("[%-2d]",i);
		/**printf the type**/

		switch(elf_phdr.p_type)
		{
		case 0:printf("\t%-6s","NULL");break;
		case 1:printf("\t%-6s","LOAD");break;
		case 2:printf("\t%-6s","DYNMIC");break;
		case 3:printf("\t%-6s","INTERP");break;
		case 4:printf("\t%-6s","NOTE");break;
		case 5:printf("\t%-6s","SHLIB");break;
		case 6:printf("\t%-6s","PHDR");break;
		case 0x70000000:printf("\t%-6s","UNDEF");break;
		case 0x7f000000:printf("\t%-6s","UNDEF");break;
		default:printf("\t%-6s","UNKOWN");break;
		}
		printf("\t0x%08x",elf_phdr.p_offset);
		printf("\t0x%08x",elf_phdr.p_vaddr);
		printf("\t0x%08x",elf_phdr.p_paddr);
		printf("\t%8d",elf_phdr.p_filesz);
		printf("\t%6d",elf_phdr.p_memsz);

		switch(elf_phdr.p_flags)
		{
		case 1:printf("%6s","  E");break;
		case 2:printf("%6s"," W ");break;
		case 4:printf("%6s","R  ");break;
		case 3:printf("%6s"," WE");break;
		case 5:printf("%6s","R E");break;
		case 7:printf("%6s","RWE");break;
		default:printf("%6s","   ");break;


		}
		printf("\t%6d",elf_phdr.p_align);
		pragram_off +=elf_header.e_phentsize;// 32 is the size of the struct elf32_Phdr
		printf("\n");
	}

}
/********
 * function: read_elf_dynstr
 *
 * description : read the information of the dynamic string table
 *
 * ***********/
char * read_elf_dynstr(Elf32_Addr name)
{

	return &tmp[elf_dynstr_off + name];



	}

/*****************
 *
 * function : read_elf_dynamic()
 *
 *
 * ********************************/

void read_elf_dynamic()
{
	Elf32_Dyn elf_dyn;
	Elf32_Dyn tmp_elf_dyn;

	int dynamic_off = 0;
	int tmp_dynamic_off = 0;
	int i;

	int dynamic_num = elf_dynamic_size / sizeof(Elf32_Dyn);

	printf("\n\nDynamic section at offset 0x%x contains %d entries:\n",
			elf_dynamic_off, dynamic_num);
	printf("Num\tTag\t\tType\t\tName/Value\n");

	for (i = 0; i < dynamic_num; i++) {

		elf_dyn.d_tag =
				*(Elf32_Sword *) &tmp[elf_dynamic_off + dynamic_off + 0];
		printf("[%-2d]", i);
		printf("\t0x%08x", elf_dyn.d_tag);

		switch (elf_dyn.d_tag) {
		case DT_NULL: {
			printf("\t%-8s", "NULL");
			break;
		}

		case DT_NEEDED: {
			printf("\t%-8s", "NEEDED");

			elf_dyn.d_un.d_val = *(Elf32_Word *) &tmp[elf_dynamic_off
					+ dynamic_off + 4];
			printf("\t%s", read_elf_dynstr(elf_dyn.d_un.d_val));
		}
			break;

		case DT_PLTRELSZ:
		{
			printf("\t%-8s", "PLTRELSZ");
			elf_dyn.d_un.d_val = *(Elf32_Word *) &tmp[elf_dynamic_off
								+ dynamic_off + 4];
			printf("\t%d(B)",elf_dyn.d_un.d_val);
		}
			break;
		case DT_PLTGOT:
		{
			printf("\t%s", "PLTGOT");
			elf_dyn.d_un.d_ptr = *(Elf32_Addr *) &tmp[elf_dynamic_off
														+ dynamic_off + 4];
						printf("\t\t0x%08x", elf_dyn.d_un.d_ptr);
		}
			break;
		case DT_HASH: {
			printf("\t%s", "HASH");
			elf_dyn.d_un.d_ptr = *(Elf32_Addr *) &tmp[elf_dynamic_off
											+ dynamic_off + 4];
			printf("\t\t0x%08x", elf_dyn.d_un.d_ptr);
		}
			break;

		case DT_STRTAB: {
			printf("\t%s", "STRTAB");
			elf_dyn.d_un.d_ptr = *(Elf32_Addr *) &tmp[elf_dynamic_off
								+ dynamic_off + 4];
			printf("\t\t0x%08x", elf_dyn.d_un.d_ptr);
		}
			break;

		case DT_SYMTAB: {
			printf("\t%s", "SYMTAB");
			elf_dyn.d_un.d_ptr = *(Elf32_Addr *) &tmp[elf_dynamic_off
											+ dynamic_off + 4];
			printf("\t\t0x%08x", elf_dyn.d_un.d_ptr);
		}
			break;

		case DT_RELA: {
			printf("\t%s", "RELA");

			elf_dyn.d_un.d_ptr = *(Elf32_Addr *) &tmp[elf_dynamic_off
														+ dynamic_off + 4];
			printf("\t\t0x%08x", elf_dyn.d_un.d_ptr);
		}
			break;

		case DT_RELASZ:
		{

			printf("\t%s", "RELASZ");
			elf_dyn.d_un.d_val = *(Elf32_Word *) &tmp[elf_dynamic_off
											+ dynamic_off + 4];
			printf("\t\t%d(B)",elf_dyn.d_un.d_val);
		}
			break;
		case DT_RELAENT: {
			printf("\t%s", "RELAENT");
			elf_dyn.d_un.d_val = *(Elf32_Word *) &tmp[elf_dynamic_off
														+ dynamic_off + 4];
						printf("\t\t%d(B)",elf_dyn.d_un.d_val);
		}
			break;

		case DT_STRSZ:
		{
			printf("\t%s", "STRSZ");
			elf_dyn.d_un.d_val = *(Elf32_Word *) &tmp[elf_dynamic_off
																	+ dynamic_off + 4];
			printf("\t\t%d(B)",elf_dyn.d_un.d_val);
		}
			break;

		case DT_SYMENT:
		{
			printf("\t%s", "SYMENT");
			elf_dyn.d_un.d_val = *(Elf32_Word *) &tmp[elf_dynamic_off
																				+ dynamic_off + 4];
						printf("\t\t%d(B)",elf_dyn.d_un.d_val);
		}
			break;

		case DT_INIT: {
			printf("\t%s", "INIT");
			elf_dyn.d_un.d_ptr = *(Elf32_Addr *) &tmp[elf_dynamic_off
					+ dynamic_off + 4];
			printf("\t\t0x%08x", elf_dyn.d_un.d_ptr);
		}
			break;

		case DT_FINI: {
			printf("\t%s", "FINI");
			elf_dyn.d_un.d_ptr = *(Elf32_Addr *) &tmp[elf_dynamic_off
								+ dynamic_off + 4];
			printf("\t\t0x%08x", elf_dyn.d_un.d_ptr);
		}
			break;

		case DT_SONAME:
		{
			printf("\t%s", "SONAME");
			elf_dyn.d_un.d_val = *(Elf32_Word *) &tmp[elf_dynamic_off
								+ dynamic_off + 4];
			printf("\t%s", read_elf_dynstr(elf_dyn.d_un.d_val));
		}
			break;

		case DT_RPATH: {
			printf("\t%s", "RPATH");
			elf_dyn.d_un.d_val = *(Elf32_Word *) &tmp[elf_dynamic_off
											+ dynamic_off + 4];
			printf("\t%s", read_elf_dynstr(elf_dyn.d_un.d_val));
		}
			break;

		case DT_SYMBOLIC:
			printf("\t%s", "SYMBOLIC");
			break;

		case DT_REL: {
			printf("\t%s", "REL");
			elf_dyn.d_un.d_ptr = *(Elf32_Addr *) &tmp[elf_dynamic_off
																	+ dynamic_off + 4];
			printf("\t\t0x%x", elf_dyn.d_un.d_ptr);
		}
			break;

		case DT_RELSZ:
		{
			printf("\t%s", "RELSZ");
			elf_dyn.d_un.d_val = *(Elf32_Word *) &tmp[elf_dynamic_off
														+ dynamic_off + 4];
			printf("\t\t%d(B)",elf_dyn.d_un.d_val);
		}
			break;

		case DT_RELENT: {
			printf("\t%s", "RELENT");
			elf_dyn.d_un.d_val = *(Elf32_Word *) &tmp[elf_dynamic_off + dynamic_off + 4];

		    printf("\t\t%d(B)",elf_dyn.d_un.d_val);
		}
			break;

		case DT_PLTREL:
		{
			printf("\t%s", "PLTREL");
			elf_dyn.d_un.d_val = *(Elf32_Word *) &tmp[elf_dynamic_off + dynamic_off + 4];
			printf("\t\t%d(B)",elf_dyn.d_un.d_val);
		}
			break;
		case DT_DEBUG:
			printf("\t%s", "DEBUG");
			break;
		case DT_TEXTREL:
			printf("\t%s", "TEXTREL");
			break;
		case DT_JMPREL:
			printf("\t%s", "JMPREL");
			break;
		case DT_BIND_NOW:
			printf("\t%s", "BIND_NOW");
			break;
		case DT_INIT_ARRAY:
			printf("\t%s", "INIT_ARRAY");
			break;
		case DT_FINI_ARRAY:
			printf("\t%s", "FINI_ARRAY");
			break;
		case DT_INIT_ARRAYSZ:
			printf("\t%s", "INIT_ARRAYSZ");
			break;
		case DT_FINI_ARRAYSZ:
			printf("\t%s", "FINI_ARRAYSZ");
			break;
		case DT_RUNPATH:
	 		printf("\t%s", "RUNPATH");
			break;
		case DT_FLAGS:
			printf("\t%s", "FLAGS");
			break;
		case DT_ENCODING:
			printf("\t%s", "ENCODING");
			break;

			//	case DT_PREINIT_ARRAY:printf("\t%s","PREINIT_ARRAY");break;

		case DT_PREINIT_ARRAYSZ:
			printf("\t%s", "PREINIT_ARRAYSZ");
			break;
		case DT_NUM:
			printf("\t%s", "NUM");
			break;
		case DT_LOOS:
			printf("\t%s", "LOOS");
			break;
		case DT_HIOS:
			printf("\t%s", "HIOS");
			break;
		case DT_LOPROC:
			printf("\t%s", "LOPROC");
			break;
		case DT_HIPROC:
			printf("\t%s", "HIPROC");
			break;
		case DT_PROCNUM:
			printf("\t%s", "PROCNUM");
			break;
		default:
			printf("\t%s", "UNKOWN");
			break;
		}

		dynamic_off += sizeof(Elf32_Dyn); //
		printf("\n");
	}
}


/*****************
 *
 * functon : read_elf_rel()
 *
 * description : read the information of the rel table
 *
 *
 *
 *
 *
 * ************************************/
void read_elf_rel_dyn()
{
	Elf32_Rel elf_rel_dyn;
	int elf_rel_dyn_num = elf_rel_dyn_size / sizeof(Elf32_Rel);
	int i =0 ;
	int rel_off = 0;
	int info_sym_temp;


	printf("\n\nRelocation section '.rel.dyn' at offset 0x%x contains %d entries:\n",elf_rel_dyn_off,elf_rel_dyn_num);
	printf(" Offset \tInfo\tType \t\tSym.Value\tSym.Name\n");
	for(; i < elf_rel_dyn_num ; i++)
	{
		elf_rel_dyn.r_offset = *(Elf32_Addr *) &tmp[elf_rel_dyn_off + rel_off + 0];
		elf_rel_dyn.r_info = *(Elf32_Word *) &tmp[elf_rel_dyn_off + rel_off + 4];



		printf("0x%x",elf_rel_dyn.r_offset	);
		printf("\t%x",elf_rel_dyn.r_info);

		switch (elf_rel_dyn.r_info & 0x000000ff )
			{
			case 0: printf("\t%-14s","R_386_NONE");break;
			case 1: printf("\t%-14s","R_386_32");break;
			case 2: printf("\t%-14s","R_386_PC32");break;
			case 3: printf("\t%-14s","R_386_GOT32");break;
			case 4: printf("\t%-14s","R_386_PLT32");break;
			case 5: printf("\t%-14s","R_386_COPY");break;
			case 6: printf("\t%-14s","R_386_GLOB_DAT");break;
			case 7: printf("\t%-14s","R_386_JMP_SLOT");break;
			case 8: printf("\t%-14s","R_386_RELATIVE");break;
			case 9: printf("\t%-14s","R_386_GOTOFF");break;
			case 10: printf("\t%-14s","R_386_GOTPC");break;
			default: printf("\t%-14s","UNDEFINE");break;
			}
		printf("\t%s",(char *) &tmp[elf_dynstr_off + ( elf_rel_dyn.r_info >> 8)- 2]);//这个地方 为什么会有这个偏移量呢？
		printf("the linker is %d, the info is %d",elf_rel_dyn_link,elf_rel_dyn_info);





		rel_off += sizeof(elf_rel_dyn);


	}
}


void read_elf_rel_plt()
{
	Elf32_Rela elf_rel_plt;
	int elf_rel_plt_num = elf_rel_plt_size / sizeof(Elf32_Rel);


	int rela_plt_off =0 ;
	int i =0;

	printf("\n\n Relocation section '.rel.plt' at offset 0x%x contains %d entries:\n",elf_rel_plt_off,elf_rel_plt_num);
	printf(" Offset \tInfo\t\tType\t\tSym.Value\tSym.Name\n");

	for(i = 0; i < elf_rel_plt_num ; i++)
		{
			elf_rel_plt.r_offset = *(Elf32_Addr *) &tmp[elf_rel_plt_off + rela_plt_off + 0];
			elf_rel_plt.r_info = *(Elf32_Word *) & tmp[elf_rel_plt_off + rela_plt_off + 4];

			printf("0x%08x",elf_rel_plt.r_offset);
			printf("\t%08x",elf_rel_plt.r_info);
			switch (elf_rel_plt.r_info &0x000000ff )
							{
							case 0: printf("\t%-14s","R_386_NONE");break;
							case 1: printf("\t%-14s","R_386_32");break;
							case 2: printf("\t%-14s","R_386_PC32");break;
							case 3: printf("\t%-14s","R_386_GOT32");break;
							case 4: printf("\t%-14s","R_386_PLT32");break;
							case 5: printf("\t%-14s","R_386_COPY");break;
							case 6: printf("\t%-14s","R_386_GLOB_DAT");break;
							case 7: printf("\t%-14s","R_386_JMP_SLOT");break;
							case 8: printf("\t%-14s","R_386_RELATIVE");break;
							case 9: printf("\t%-14s","R_386_GOTOFF");break;
							case 10: printf("\t%-14s","R_386_GOTPC");break;
							default: printf("\t%-14s","UNDEFINE");break;
						}
			printf("\t%s",(char *) &tmp[elf_dynstr_off + ( elf_rel_plt.r_info >> 8)]);
			printf("\t%s",(char *) &tmp[elf_dynsym_off + ELF32_R_SYM(elf_rel_plt.r_info)]);


			printf("the linker is %d, the info is %d",elf_rel_plt_link,elf_rel_plt_info);

			rela_plt_off += sizeof(Elf32_Rel);
			printf("\n");
		}

}
/*****************
 *
 * function: read_elf_plt
 *
 * description : read the information of the plt
 *
 *
 *
 *
 *
 * *****************/
void read_elf_plt()
{



}

/**************************
 * function : read_elf_plt
 *
 * description : read the information of got
 *
 *
 *
 *
 *
 *
 *
 * *************************************/
void read_elf_got()
{
	int i ;
	int got_num = elf_got_size / sizeof(int);
	int tmp_got_off = 0;
	printf("Got contents pos info ...\n");
	printf("section '.got.plt' at offset 0x%x contains %d entries:\n",elf_got_off,got_num);

	for(i = 0; i < got_num ;i++)
	{
		printf("0x%08x\n",tmp[elf_got_off + tmp_got_off]);
		tmp_got_off +=sizeof(int);






	}






}

/****************************************
 *
 * function : read the information of dynsym
 *
 *
 *
 *
 * ******************************/
void read_elf_dynsym()
{
	Elf32_Sym elf_dynsym;

	int dynsym_off = 0;

	int dynsym_num = (elf_dynsym_size / sizeof(Elf32_Sym) );
	printf("Dynamic symbol table '.dynsym' contains [%-2d] entries:\n",dynsym_num);
	int i;

	printf("Num\tValue\t\tSize\tType\tBind\tother\tNdx\tName\n");
	for( i=0; i < dynsym_num; i++)
	{
		elf_dynsym.st_name = *((Elf32_Word *) &tmp[elf_dynsym_off + dynsym_off + 0]);
		elf_dynsym.st_value = *(Elf32_Addr *) &tmp[elf_dynsym_off + dynsym_off + 4];
		elf_dynsym.st_size = *(Elf32_Word *) &tmp[elf_dynsym_off + dynsym_off + 8];
		elf_dynsym.st_info = *(unsigned char *) &tmp[elf_dynsym_off + dynsym_off + 12];
		elf_dynsym.st_other = *(unsigned char *) &tmp[elf_dynsym_off + dynsym_off + 13];
		elf_dynsym.st_shndx = *(Elf32_Half *) &tmp[elf_dynsym_off + dynsym_off + 14];
		printf("[%2d]",i);

		printf("\t0x%08x",elf_dynsym.st_value);

		printf("\t%d",elf_dynsym.st_size);

		/**printf the information of type**/
		switch( (elf_dynsym.st_info) & 15)
		{
		case 0:printf("\t%s","NOTYPE");break;
		case 1:printf("\t%s","OBJECT");break;
		case 2:printf("\t%s","FUNC");break;
		case 3:printf("\t%s","SECTION");break;
		case 4:printf("\t%s","FILE");break;
		case 13:printf("\t%s","LOPROC");break;
		case 15:printf("\t%s","HIPROC");break;
		}

		/***print the information of Binding***/
		switch( (elf_dynsym.st_info>>4))
		{
		case 0:printf("\tLOCAL");break;
		case 1:printf("\tGLOBAL");break;
		case 2:printf("\tWEAK");break;
		case 13:printf("\tLOPROC");break;
		case 15:printf("\tHIPROC");break;
		default:printf("\tUND");break;
		}

		printf("\t%-4d",elf_dynsym.st_other);


		/***printf the information of shndx**/
		switch(elf_dynsym.st_shndx)
		{
			case 0xfff1:printf("\t%-6s","ABS");break;
			case 0xfff2:printf("\t%-6s","COMMON");break;
			case 0:     printf("\t%-6s","UND");break;
			default:printf("\t%d ",elf_dynsym.st_shndx);break;
		}


		printf(" %s",(char *)&tmp[elf_dynstr_off + elf_dynsym.st_name]); //note: the elf_dynstr_off
		dynsym_off +=sizeof(Elf32_Sym);// 递增的结构
		printf("\n");


	}
}
/********************
 *
 *
 *
 *
 *
 *
 * *********************************/

void read_elf_interp()
{
	printf("\nRequesting program interpreter : %s\n\n ", (char *)&tmp[elf_interp_off]);

}

/***********************
 *
 *
 *
 *
 *
 * *******************************/

/********
 *
 * main
 *
 *
 * *********/

void main(int argc, char ** argv) {



	/**验证参数**/
	if (argc < 2) {
		printf("failed!\n Less arguments! the useage : ./readelf filename  \n");
		return;
	}
	printf("open the file %s\n", argv[1]);

	int fd ;
	fd = open(argv[1],O_RDONLY);
	if( -1 == fd)
	{
		printf("open the file failed!\n");
		return ;
	}

	if(-1 == read(fd,&tmp,MAX_SIZE) )
	{
		printf("read the file failed!\n");
		return;
	}
	close(fd);
    /****printf the information of the elf header information*******/
	read_elf_header(argv[1]);
	printf("\n");

	/**printf the information of the elf section header***/
	read_elf_shdr(argv[1]);
	printf("\n");
	read_elf_symtab();
	printf("\n");
//	read_elf_rela();

	/*****read the information of program header i******/
	read_elf_program_header();

	printf("\n");
	read_elf_dynamic();

	printf("\n");

	read_elf_rel_dyn();
	printf("\n");
	read_elf_rel_plt();

	printf("\n");

	read_elf_dynsym();
	printf("\n");
	read_elf_plt();
	printf("\n");
	read_elf_got();


	 read_elf_interp();







}
