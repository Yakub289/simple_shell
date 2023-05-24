#ifndef _HELPERS_H_
#define _HELPERS_H_

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <stddef.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

/* Buffering */
#define READ_BUF_SIZE		1024
#define WRITE_BUF_SIZE		1024
#define BUF_FLUSH		-1
#define HIST_FILE		".simple_shell_history"
#define HIST_MAX		4096


/* Command line */
#define CMD_NORM		0
#define CMD_OR			1
#define CMD_AND			2
#define CMD_CHAIN		3
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2
#define USE_GETLINE		0
#define USE_STRTOK		0

#endif /* _HELPERS_H_ */
