#define _GNU_SOURCE
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

bool isstrdigit(const char* str, size_t len) {
    for (size_t i = 0; i < len; i ++) {
        if (!isdigit(*str++)) {
            return false;
        }
    }
    return true;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <number> or %s <SIGXXX>\n", argv[0], argv[0]);
        return 1;
    }

    char* arg = argv[1];
    if (isstrdigit(arg, strlen(arg))) {
        int signal = (int) strtol(arg, NULL, 10);
        const char* str = sigabbrev_np(signal);
        if (str != NULL) {
            printf("SIG%s\n", str);
            return 0;
        }
    } else {
        char prefix[] = "SIG";
        size_t prefix_size = sizeof(prefix);
        char* sigstr = arg;
        if (strncasecmp(prefix, arg, prefix_size) == 0) {
            // the argument is in form SIGXXX, strip the SIG part
            sigstr = sigstr + prefix_size;
        }
        for (int i = 1; i < NSIG; i ++) {
            const char* candidate = sigabbrev_np(i);
            if (candidate == NULL) continue;
            if (strcasecmp(sigstr, candidate) == 0) {
                printf("%d", i);
                return 0;
            }
        }
    }
    fprintf(stderr, "Unknown signal %s\n", arg);
    return 1;
}
