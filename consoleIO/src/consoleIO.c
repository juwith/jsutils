#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <getopt.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

#define CIO_DEBUG(FormatLiteral, ...)  fprintf (stderr, CYN "[%s:%d] " FormatLiteral "\n" RESET, __func__, __LINE__, ##__VA_ARGS__)
#define CIO_WARNING(FormatLiteral, ...)  fprintf (stderr, YEL "[%s:%d] " FormatLiteral "\n" RESET, __func__, __LINE__, ##__VA_ARGS__)
#define CIO_ERROR(FormatLiteral, ...)  fprintf (stderr, RED "[%s:%d] " FormatLiteral "\n" RESET, __func__, __LINE__, ##__VA_ARGS__)

typedef enum
{
	ST_ConsoleCmd_None = -1,
	ST_ConsoleCmd_Create,
	ST_ConsoleCmd_Destroy,
	ST_ConsoleCmd_Func1,
	ST_ConsoleCmd_Func2,
	ST_ConsoleCmd_Func3,
	ST_ConsoleCmd_Func4,
	ST_ConsoleCmd_Exit,
	ST_ConsoleCmd_Help,
	ST_ConsoleCmd_Max
} ST_ConsoleCmd_E;

typedef struct
{
	char *pstrCmd;

	ST_ConsoleCmd_E eCmd;
} ST_ConsoleCmd_T;

ST_ConsoleCmd_T G_tConsoleCmd[ST_ConsoleCmd_Max] = {
	{"create", ST_ConsoleCmd_Create},
	{"destroy", ST_ConsoleCmd_Destroy},
	{"func1", ST_ConsoleCmd_Func1},
	{"func2", ST_ConsoleCmd_Func2},
	{"func3", ST_ConsoleCmd_Func3},
	{"func4", ST_ConsoleCmd_Func4},
	{"exit", ST_ConsoleCmd_Exit},
	{"help", ST_ConsoleCmd_Help}
};

typedef struct tag_CIO_Instance_T
{
	bool bStateAlive;

	int iSelectedID;
} CIO_Instance_T;

static void ST_FUNC_Exit(CIO_Instance_T * ptCIO)
{
	ptCIO->bStateAlive = false;
}

static void ST_FUNC_Help(void)
{
	printf("\n");
	printf("################################## Setting Help ############################\n");
	printf("# \n");
	printf("# create\n");
	printf("# destroy\n");
	printf("# \n");
	printf("################################## function Help ###########################\n");
	printf("# func1\n");
	printf("# func2\n");
	printf("# func3\n");
	printf("# func4\n");
	printf("# exit\n");
	printf("# help\n");
	printf("# \n");
	printf("############################################################################\n");
	printf("# \n");
	printf("Enter string below [ctrl + d] to quit\n\n\n");
}

static int ST_FUNC_event_callback(void *pvPrivate, int eEvent, void *pvParam)
{
	return 0;
}

static char* ST_FUNC_parse_input_cmd(char** dest, int *ntoken, char* cmd)
{
	int i=0;
	char *strBuff = NULL;

	if(dest == NULL)
		return NULL;

	strBuff = strdup(cmd);
	*dest = strtok(strBuff," ,\n");

	if(*dest == NULL)
	{
		//input command is null => return func
		if(strBuff)
		{
			free(strBuff);
		}
		return NULL;
	}
	*dest++;
	i++;

	while(*dest = strtok(NULL," ,\n"))
	{
		*dest++;
		i++;
	}

	if(ntoken != NULL)
		*ntoken = i;

	return strBuff;
}

static int ST_FUNC_Console_CB(char *cmdline, void *pvPrivate)
{
	int iArgs = 0;
	char *pcArgs[10] = {NULL, };
	int iSelectedID;

	ST_ConsoleCmd_E eCmd = ST_ConsoleCmd_None;

	CIO_Instance_T *ptInstance = (CIO_Instance_T *)pvPrivate;

	if(ptInstance == NULL)
	{
		CIO_DEBUG("Check instance initialize");
		return -1;
	}

	char* cmdbuff = ST_FUNC_parse_input_cmd(pcArgs,&iArgs,cmdline);
	if(cmdbuff == NULL)
	{
		return -1;
	}

	for(int i = 0; i < ST_ConsoleCmd_Max; i++)
	{
		if(strcmp(pcArgs[0], G_tConsoleCmd[i].pstrCmd) == 0)
		{
			eCmd = G_tConsoleCmd[i].eCmd;
			break;
		}
	}

	switch(eCmd)
	{
	case ST_ConsoleCmd_Create:
		{
			CIO_DEBUG("dummy create");
		}
		break;
	case ST_ConsoleCmd_Destroy:
		{
			CIO_DEBUG("dummy destroy");
		}
		break;
	case ST_ConsoleCmd_Func1:
		{
			CIO_DEBUG("dummy func1");
		}
		break;
	case ST_ConsoleCmd_Func2:
		{
			CIO_DEBUG("dummy func2");
		}
		break;
	case ST_ConsoleCmd_Func3:
		{
			CIO_DEBUG("dummy func3");
		}
		break;
	case ST_ConsoleCmd_Func4:
		{
			CIO_DEBUG("dummy func4");
		}
		break;
	case ST_ConsoleCmd_Exit:
		{
			ST_FUNC_Exit(ptInstance);
		}
		break;
	case ST_ConsoleCmd_Help:
		{
			CIO_DEBUG("input help");
			ST_FUNC_Help();
		}
		break;
	}

	free(cmdbuff);

	return 0;
}

static void ST_Deinit_CIO(CIO_Instance_T* cio)
{
	CIO_Instance_T *ptInstance = cio;
	CIO_DEBUG("deinit");

	free(ptInstance);
}

static void usage(char* name)
{
	printf(
		"Usage: latency [OPTION]... [FILE]...\n"
		"ex) %s\n",name
	);

	printf("-h help\n");

	printf("\n\nHow to input your command on running background\n");
	printf(
		"make pipe\n"
		"```\n"
		"\t mkfifo input.pipe\n"
		"\t (tail -f input.pipe) | %s > %s.log &\n", name, name
		);
	printf(
		"```\n"
		"input command\n"
		"```\n"
		"\t echo \"func1 \" > input.pipe\n"
		"```\n"
	);

}

int main(int argc, char **argv)
{
	CIO_Instance_T *ptInstance;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int iHelp = 0;

	int c;
	while((c = getopt(argc, argv, "h")) != -1)
	{
		switch(c)
		{
			case 'h':
			default:
				usage(argv[0]);
				exit(1);
			break;
		}
	}

	ptInstance = (CIO_Instance_T *)calloc(sizeof(CIO_Instance_T), 1);
	ptInstance->bStateAlive = true;

	ST_FUNC_Help();

	while((read = getline(&line, &len, stdin)) != -1)
	{
		if (read > 0)
		{
			//printf("\n  read %zd chars from stdin, allocated %zd bytes for line : %s\n", read, len, line);
			ST_FUNC_Console_CB(line,ptInstance);
			if(strcmp(line,"\n") == 0)
			{
				iHelp++;
			}
			if(iHelp > 5)
			{
				CIO_DEBUG("do you need help?");
				ST_FUNC_Help();
				iHelp = 0;
			}
		}

		if(ptInstance->bStateAlive == false)
		{
			printf ("exit\n");
			break;
		}
	}

	ST_Deinit_CIO(ptInstance);
	free(line);

	return 0;
}
