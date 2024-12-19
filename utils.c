#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <err.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <netinet/in.h>

#include "utils.h"

// BUG: Integer overflow possible!
ssize_t strmcat(char *dst, char *src, size_t dst_cap)
{
	size_t dst_len = strlen(dst);
	size_t src_len = strlen(src);
	if (dst_len + src_len > dst_cap - 1) {
		return -1;
	} else {
		strcpy(dst + dst_len, src);
		return dst_len + src_len;
	}
}

ssize_t strmcatx(char *dst, char *src, size_t dst_cap)
{
	size_t l = strmcat(dst, src, dst_cap);
	if (l <= 0) {
		errx(EXIT_FAILURE, "Buffer too small");
	}
	return l;
}

void sendx(int fd, char *content)
{
	sendc(fd, content, strlen(content), 0);
}

void sendc(int fd, char *buf, size_t n, int flags)
{
	ssize_t slen = send(fd, buf, n, flags);
	if (slen < 0) {
		err(EXIT_FAILURE, "send");
	} else if ((size_t)slen == n) {	// slen cannot be negative at this point.
		return;
	} else {
		errx(EXIT_FAILURE, "send returned invalid length");
	}
}

void sendbx(int fd, char content)
{
	sendc(fd, &content, 1, 0);
}

// len must be nonzero.
size_t recvx(int fd, char *buf, size_t len)
{
	ssize_t rlen = recv(fd, buf, len, 0);
	if (rlen < 0) {
		err(EXIT_FAILURE, "recv");
	} else if (rlen == 0) {
		errx(EXIT_FAILURE, "disconnected");
	} else {
		return rlen;
	}
}

