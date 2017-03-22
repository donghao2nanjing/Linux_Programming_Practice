#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <time.h>

void do_ls(char[]);
void show_file_info(char * filename , struct stat * statbufp );
void mode2letter(int mode , char str[]);
void print_uid2name(uid_t uid );
void print_gid2name(gid_t gid );

int main(int ac , char * av[])
{
	if(ac == 1 )
	{
		do_ls(".");
	}
	else
	{
		while( -- ac )
		{
			printf("%s:\n", * (++ av) );
			do_ls(*av);
		}
	}
	return 0 ;
}

void do_ls(char dirname[])
{
	DIR * dir_ptr ;
	struct dirent * direntp ;
	struct stat statbuf ;

	if( ( dir_ptr = opendir(dirname) )== NULL )
	{
		fprintf(stderr, "ls1 can not open %s\n", dirname );
	}
	else
	{
		while( ( direntp = readdir(dir_ptr ) ) != NULL )
		{
			if( stat(direntp -> d_name , &statbuf) == -1 )
			{
				perror(direntp -> d_name );
			}
			else
			{
				show_file_info( direntp -> d_name , &statbuf);
			}
		}
	}

	closedir(dir_ptr);
}

void show_file_info( char * filename, struct stat * statbufp )
{
	char modestr[11]; // include '\0' so 10 + 1 = 11

	mode2letter(statbufp -> st_mode , modestr) ;
	printf("%s",  modestr );

	printf("%4d", (int)statbufp -> st_nlink ) ;
	print_uid2name( statbufp -> st_uid ) ;
	print_gid2name( statbufp -> st_gid ) ;
	printf("%8ld", (long) (statbufp -> st_size) );
	printf(" %12.12s", (char*)(4 + ctime(&(statbufp -> st_mtime)) ));
	printf(" %s\n",filename );
}

void mode2letter(int mode , char str[])
{
	strcpy(str , "----------");

	if( S_ISDIR( mode ))
		str[0] = 'd' ;
	else if( S_ISCHR( mode ))
		str[0] = 'c' ;	// else for efficience
	else if( S_ISBLK( mode ))
		str[0] = 'b' ;

	if( mode & S_IRUSR )
		str[1] = 'r' ;
	if( mode & S_IWUSR )
		str[2] = 'w' ;
	if(mode & S_IXUSR )
		str[3] = 'x' ;

	if( mode & S_IRGRP )
		str[4] = 'r' ;
	if( mode & S_IWGRP )
		str[5] = 'w' ;
	if( mode & S_IXGRP )
		str[6] = 'x' ;

	if( mode & S_IROTH )
		str[7] = 'r' ;
	if( mode & S_IWOTH )
		str[8] = 'w' ;
	if( mode & S_IXOTH )
		str[9] = 'x' ;
}

void print_uid2name( uid_t uid )
{
	struct passwd * passwdbufp ;

	if(( passwdbufp = getpwuid(uid)) != (struct passwd *)NULL ) // Except for error
	{
		printf( "%-8s" , passwdbufp -> pw_name ) ;
	}
	else
	{
		printf( "%8d" , uid) ;
	}

}

void print_gid2name(gid_t gid)
{
	struct group * grp_ptr ;
	if(( grp_ptr = getgrgid(gid)) != (struct group * )NULL )
	{
		printf("%-8s" , grp_ptr -> gr_name ) ;
	}
	else
	{
		printf("%8d" , gid ) ;
	}
}
