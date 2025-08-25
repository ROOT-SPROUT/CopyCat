#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "copycat.h"

int main(int argc, char *argv[]){
    int opt;

    int recursive = 0 , force = 0, help = 0;

    while ((opt = getopt(argc, argv, "rfh")) != -1){
        switch (opt){
            case 'r':
                recursive = 1;
                break;
            case 'f':
                force = 1;
                break;
            case 'h':
                help = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-rfh] <source_file> <destination_file>\n", argv[0]);
                return 1;
        }
    }

    if (help){
        printf("Usage: %s [-rfh] <source_file> <destination_file>\n", argv[0]);
        printf("Options:\n");
        printf("  -r    Recursive copy\n");
        printf("  -f    Force copy (overwrite existing files)\n");
        printf("  -h    Display this help message\n");
        return 0;
    }

    int paths_count = argc - optind;

    if (paths_count < 2){
        printf("Error: Missing source or destination file\n");
        return 1;
    }

    char **sources = &argv[optind]; // Array of source file paths
    int source_count = paths_count - 1;
    char *dest = argv[argc - 1];

    if (source_count == 1){
        simplecopy(sources[0], dest, recursive, force);
    }
    else{
        // Multiple source files
        for (int i = 0; i < source_count; i++){
            // Construct destination path by appending basename of source to dest
            char dest_path[1024];
            const char *src_basename = strrchr(sources[i], '/');
            if (!src_basename) src_basename = sources[i];
            else src_basename++;
            snprintf(dest_path, sizeof(dest_path), "%s/%s", dest, src_basename);
            simplecopy(sources[i], dest_path, recursive, force);
        }
    }

    return 0;
}