#include <unistd.h>
#include <iostream>
#include <string>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>

using namespace std;

const int MAX_SIZE = 1024;

int main() {
    string file_name;
    cin >> file_name;

    int file = open(file_name.c_str(), O_RDONLY);
    
    string shmpath = "just_memory_space";


    int fd = shm_open(shmpath.c_str(), O_CREAT | O_RDWR, S_IREAD | S_IWRITE);

    if (fd == -1) {
        cerr << "shm_open err1\n";
    }
                   

    if (ftruncate(fd, sizeof(char)* MAX_SIZE) == -1) {
        cerr << "ftruncate\n";
    }


    char* data = (char*) mmap(NULL, (sizeof(char)* MAX_SIZE), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);


    pid_t pid = fork();
    if (pid == -1) {
        cout << "Error fork!\n";
        return 1;

    } else if (pid == 0) {

        dup2(file, STDIN_FILENO);
        
        execl("./child", "./child", shmpath.c_str(), NULL);

        for (char el :"Ошибка запуска дочернего процесса!") {
            write(STDERR_FILENO, &el, sizeof(char));
        }

    } else {
        wait(0);
        for (int i = 0; i < MAX_SIZE; i++) {
            cout << data[i];
        }
        munmap(data, (sizeof(char)* MAX_SIZE));
        shm_unlink(shmpath.c_str());
        close(file);
    }


return 0; 
}
