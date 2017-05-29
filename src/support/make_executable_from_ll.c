#include <stdlib.h>
#include <stdio.h>

void make_executable_from_ll(const char *ll_file_path, const char *output_file_name) {
    const char *tmp_s_file_path = "/tmp/__tmp.s";
    char llc_command[128], gcc_command[128];
    sprintf(llc_command, "\"$(which llc || echo \"`brew --prefix llvm`/bin/llc\")\" %s -o %s", ll_file_path, tmp_s_file_path);
    sprintf(gcc_command, "gcc %s -o %s; rm %s", tmp_s_file_path, output_file_name, tmp_s_file_path);
    system(llc_command);
    system(gcc_command);
}
