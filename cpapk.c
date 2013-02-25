#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/io.h>

#define MAX_LEN 255
#define WORKDIR "/home/yourname/workdir/"
#define APKDIR "/apkdir/"
#define TARGET "apk/"

#ifndef WARN_ERROR_STR
#define ERROR_NOT_EXIST "ERROR: File is not exist"
#define ERROR_NO_ARGS "ERROR: No args for this command"
#define ERROR_NO_PROJECT_NAME "ERROR: No project name"
#define ERROR_NO_APK_NAME "ERROR: No apk name"
#endif


int main(int argc, const char *argv[])
{
	int ret = 0;
	char *project_name = NULL, *apk_name = NULL;
	char filepath[MAX_LEN] = "";
	const char *strMenu = "===========================\n"
						"cpapk [arg1] [arg2]\n"
						"h display help menu\n"
						"arg1 project name\n"
						"arg2 apk name\n"
						"[Example]\n"
						"cpapk project1 file1.name\n"
						"which is equals to:\n"
						"cp /home/yourname/workdir/project1/apkdir/file1.name /home/yourname/destdir";

	if (argc > 1) // args more than one
	{
		if (0 == strcmp(argv[1], "h")) // detect if it is 'h': help menu
		{
			printf("%s\n", strMenu);
		}
		else // format file path and detect if it's avaliable or not
		{
			project_name = malloc(sizeof(argv[1]));
			strcpy(project_name, argv[1]);
			if (argc > 2)
			{
				apk_name = malloc(sizeof(argv[2]));
				strcpy(apk_name, argv[2]);
			}

			#ifdef MDEBUG
				assert(NULL != project_name);
				assert(NULL != apk_name);
			#else
				if (NULL == project_name)
				{
					printf("%s\n", ERROR_NO_PROJECT_NAME);
					exit(EXIT_FAILURE);
				}
				if (NULL == apk_name)
				{
					printf("%s\n", ERROR_NO_APK_NAME);
					exit(EXIT_FAILURE);
				}
			#endif

			ret |= (sprintf(filepath, "%s%s%s%s", WORKDIR, project_name, APKDIR, apk_name)) << 4;
			ret |= (access(filepath, 0));

			if (0 == ret&0xf)
			{
				FILE *source, *target;
				char *tmp = NULL;
				unsigned char byte;
				int val = 0;

				source = fopen(filepath, "rb");
				if( source == NULL )
				{
					printf("Press any key to exit...\n");
					exit(EXIT_FAILURE);
				}

				tmp = malloc(MAX_LEN);
				strcat(tmp, TARGET);
				strcat(tmp, apk_name);
				target = fopen(tmp, "wb");
				if( target == NULL )
				{
					fclose(source);
					printf("Press any key to exit...\n");
					exit(EXIT_FAILURE);
				}

				while(1) { //infinant loop
					val = fgetc(source);
					if (val == EOF) break;
					byte = (unsigned char) val;
					fputc(byte,target);
				}

				getchar();
				fclose(source);
				fclose(target);
				free(tmp);
			}
			else
			{
				printf("%s\n", ERROR_NOT_EXIST);
			}
		}
	}
	else // no args
	{
		printf("%s\n", ERROR_NO_ARGS);
	}

	return ret;
}
