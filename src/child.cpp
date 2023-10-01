#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]) {

    char c, enter = '\n';
    float num = 0, res;
    int counter = 0, isfirstnum = 1;
    while (read(STDIN_FILENO, &c, sizeof(c)) != 0) {

        if (c == ' ') {

            if (isfirstnum == 1) {
                res = num;
                isfirstnum = 0;

            } else {
                if (num != 0) res /= num;
                else return 1;
            }
            num = 0;
            counter = 0;

        } else if (c == '.') counter = 10;

        else if (c == '\n') {
            if (num != 0) {
                res /= num;
                string buf = to_string(res);

                for (char el : buf) {
                    write(STDOUT_FILENO, &el, sizeof(el));
                }
                write(STDOUT_FILENO, &enter, sizeof(char));

                counter = 0;
                isfirstnum = 1;
                num = 0;

            } else return 1;
            
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
return 0;
}
