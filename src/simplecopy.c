#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <copycat.h>

int simplecopy(const char* source_file, const char* dest_file, int recursive, int force){

    int source_fd = open(source_file, O_RDONLY);

    if (source_fd == -1){
        perror("Error opening source file");
        return 1;
    }

    int destination_fd;

    if (!force) {
        destination_fd = open(dest_file, O_WRONLY | O_CREAT | O_EXCL, 0644);
    } else {
        destination_fd = open(dest_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    }

    if (destination_fd == -1){
        close(source_fd);
        perror("Error opening destination file, if it exists please use force option -f");
        return 1;
    }

    char buffer[2048];
    ssize_t bytes_read;

    while((bytes_read = read(source_fd, buffer, sizeof(buffer))) > 0){
        write(destination_fd, buffer, bytes_read);
    }

    close(source_fd);
    close(destination_fd);

    return 0;
}