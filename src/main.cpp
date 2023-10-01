#include <unistd.h>
#include <iostream>
#include <string>
#include <fcntl.h>

using namespace std;

int main() {
    string file_name;
    char el;
    while (read(STDIN_FILENO, &el, sizeof(char))!=0) {
        if (el != '\n') file_name.push_back(el);
        else break;
    }

    int file = open(file_name.c_str(), O_RDONLY);
    if (file == -1) {
        for (char el : "error pipe\n") {
            write(STDERR_FILENO, &el, sizeof(char));
        }
        return 1;
    }

    int pipefd[2];
    if (pipe(pipefd) == -1){
        for (char el : "error pipe\n") {
            write(STDERR_FILENO, &el, sizeof(char));
        }
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1) {

        for (char el :"error fork\n") {
            write(STDERR_FILENO, &el, sizeof(char));
        }
        return 1;

    } else if (pid == 0) {

        close(pipefd[0]);

        dup2(file, STDIN_FILENO);
        dup2(pipefd[1], STDOUT_FILENO);

        execl("./child", "child", NULL);

        for (char el :"Ошибка запуска дочернего процесса!") {
            write(STDERR_FILENO, &el, sizeof(char));
        }

    } else {

        close(pipefd[1]);
        
        char p;
        while ((read(pipefd[0], &p, sizeof(p))) != 0) {
            write(STDOUT_FILENO, &p, sizeof(p));
        }

        for (char el : "You want to '/' with zero.\n") {
            write(STDERR_FILENO, &el, sizeof(el));
        }

    close(pipefd[0]);
    close(file);
    }
return 0; 
}
