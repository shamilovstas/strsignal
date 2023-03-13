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

void print_sig_table(void) {
    for (int i = 1; i < NSIG; i ++) {
        const char* signame = sigabbrev_np(i);
        if (signame == NULL) continue;
        printf("%d\tSIG%s\n", i, signame);
    }
}

/**
 * Get signal value by its name
 * @param signame Name of a signal (may be in a form SIGXXX or just XXX)
 * @return Signal value or -1 if a signal with this value is not found
 */
int get_sig_value(const char* signame) {
    char prefix[] = "SIG";
    size_t prefix_size = sizeof(prefix);
    const char* sigstr = signame;
    if (strncasecmp(prefix, signame, prefix_size - 1) == 0) { // -1 for \0 byte
        // the argument is in form SIGXXX, strip the SIG part
        sigstr = sigstr + prefix_size - 1;
    }
    for (int i = 1; i < NSIG; i ++) {
        const char* candidate = sigabbrev_np(i);
        if (candidate == NULL) continue;
        if (strcasecmp(sigstr, candidate) == 0) {
            return i;
        }
    }
    return -1;
}

void print_sig_not_found(const char* const arg) {
    fprintf(stderr, "Unknown signal %s\n", arg);
    exit(1);
}

int print_str_signal(char* arg) {
    int ret = 0;
    if (isstrdigit(arg, strlen(arg))) {
        int signal = (int) strtol(arg, NULL, 10);
        const char* str = sigabbrev_np(signal);
        if (str != NULL) {
            printf("SIG%s\n", str);
        } else {
            ret = -1;
        }
    } else {
        int sigvalue = get_sig_value(arg);
        if (sigvalue == -1) {
            ret = -1;
        } else {
            printf("%d\n", sigvalue);
        }
    }
    return ret;
}

int main(int argc, char** argv) {
    if (argc == 1) {
        printf("Value\tName\n");
        print_sig_table();
        return 0;
    } else if (argc == 2) {
        char* arg = argv[1];
        int ret = print_str_signal(arg);
        if (ret < 0) {
            print_sig_not_found(arg);
        } else {
            return 0;
        }
    } else {
        fprintf(stderr, "usage: %s <number> or %s <SIGXXX>\n", argv[0], argv[0]);
        return 1;
    }
}
