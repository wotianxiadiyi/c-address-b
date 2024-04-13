#include <stdio.h>
#include <string.h>

#include "neko.inc.c"

enum mode
{
    MODE_STDIN,
    MODE_ARGV
};

struct stats
{
    int max_len;
    int lines;
};

const char *delim = " \t\n";

// gets the max line-by-line length of a buffer
// will consume the buffer
void get_stats(char *buffer, int wrap, struct stats *stats)
{
    char *state;
    const char *tok;
    tok = strtok_r(buffer, delim, &state);
    int pos = 0;
    stats->max_len = 0;
    stats->lines = 0;
    do {
        int len = strlen(tok);
        if (pos + len > wrap) {
            stats->max_len = pos > stats->max_len ? pos : stats->max_len;
            pos = 0;
            stats->lines += 1;
            pos = len;
        } else {
            pos = pos + len + 1;
        }
    } while ((tok = strtok_r(NULL, delim, &state)));
    if (stats->lines == 0) pos = pos - 1;
    stats->max_len = pos > stats->max_len ? pos : stats->max_len;
}

// jank as heck
void say(char *buffer, struct stats *stats, const char *cat)
{
    // print beginning
    fputc(' ', stdout);
    for (int i = 0; i < stats->max_len + 2; ++i) fputc('~', stdout);
    fputc('\n', stdout);

    // print contents
    char *state;
    const char *tok;
    tok = strtok_r(buffer, delim, &state);
    int pos = 0;
    int line = 0;
    char line_beg, line_end;
    if (stats->lines == 0) {
        line_beg = '{';
        line_end = '}';
    } else if (line == 0) {
        line_beg = '/';
        line_end = '\\';
    }
    if (pos == 0) {
            fputc(line_beg, stdout);
            fputc(' ', stdout);
    }
    do {
        int len = strlen(tok);
        if (pos + len > stats->max_len) {
            // finish the line
            for (int i = pos; i < stats->max_len; ++i) {
                fputc(' ', stdout);
            }
            fputc(' ', stdout);
            fputc(line_end, stdout);
            // new line
            if (line == stats->lines - 1) {
                line_beg = '\\';
                line_end = '/';
            } else {
                line_beg = '|';
                line_end = '|';
            }
            fputc('\n', stdout);
            fputc(line_beg, stdout);
            fputc(' ', stdout);

            line += 1;
            printf("%s", tok);
            pos = len;
        } else {
            printf("%s", tok);
            pos = pos + len;
        }
        tok = strtok_r(NULL, delim, &state);
        if (tok) {
            pos += 1;
            fputc(' ', stdout);
        }
    } while (tok);

    // finish the line
    for (int i = pos; i < stats->max_len; ++i) {
        fputc(' ', stdout);
    }
    fputc(' ', stdout);
    fputc(line_end, stdout);
    fputc('\n', stdout);

    // print end
    fputc(' ', stdout);
    for (int i = 0; i < stats->max_len + 2; ++i) fputc('~', stdout);
    fputc('\n', stdout);

    // print cat
    puts(cat);
}

char read_buffer[4096];
char buffer[4096];
int main(int argc, char *argv[])
{
    int wrap = 40;
    int mode = 0;
    if (argc > 1) {
        if (!strcmp("-h", argv[1]) || !strcmp("--help", argv[1])) {
            puts("usage: nekosay [string]");
            puts(neko);
            return 0;
        }

        // copy arg
        snprintf(buffer, sizeof(buffer), "%s, nyaa~", argv[1]);
        read_buffer[sizeof(read_buffer)-1] = '\0';
    } else {
        // read in string
        size_t size = fread(read_buffer, 1, sizeof(read_buffer)-1, stdin);
        read_buffer[size-1] = '\0';
        snprintf(buffer, sizeof(buffer), "%s, nyaa~", read_buffer);
    }

    // copy back to readbuffer for second pass
    memcpy(read_buffer, buffer, sizeof(buffer));
    struct stats stats;
    get_stats(read_buffer, wrap, &stats);
    say(buffer, &stats, neko);

    return 0;
}
