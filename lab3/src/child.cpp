#include <unistd.h>
#include <iostream>
#include <string>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>

using namespace std;

const int MAX_SIZE = 1024;

int main(int argc, char *argv[]) {

    int fd = shm_open(argv[1], O_CREAT | O_RDWR, S_IREAD | S_IWRITE);

    if (ftruncate(fd, sizeof(char)* MAX_SIZE) == -1) {
        cerr << "ftruncate2\n";
    }


    char* data = (char*) mmap(NULL, (sizeof(char)* MAX_SIZE), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    char c, enter = '\n';
    float num = 0, res;
    int counter = 0, isfirstnum = 1, ind = 0;

    while (read(STDIN_FILENO, &c, sizeof(c)) != 0) {

        if (c == ' ') {

            if (isfirstnum == 1) {
                res = num;
                isfirstnum = 0;

            } else {
                if (num != 0) {
                    res /= num;
                }
                else {
                    for (char el: "You want to '/' with zero.\n") {
                        data[ind++] = el;
                    }
                    return 1;
                }
                
            }
            num = 0;
            counter = 0;

        } else if (c == '.') {
            counter = 10;
        }

        else if (c == '\n') {
            if (num != 0) {
                res /= num;
                string buf = to_string(res);
                for (char el : buf) {
                    data[ind++] = el;
                }
                data[ind++] = enter;

                counter = 0;
                isfirstnum = 1;
                num = 0;

            } else {
                for (char el: "You want to '/' with zero.\n") {
                    data[ind++] = el;
                }
                return 1;
            }
                
            
        } else {
            if (counter == 0) {
                num *= 10;
                num += c - '0'; 
            } else {
                num += (float)(c - '0') / counter;
                counter *= 10;
            }
        }
    }
    munmap(data, (sizeof(char)* MAX_SIZE));
return 0;
}
