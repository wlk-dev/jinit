#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <Windows.h>

void setcolor(int color) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void make_file(char *fname) {
        if (access(fname, F_OK) == 0) {
                setcolor(4); // 4 = RED
                printf("[mkf] %s already exists, skipping...\n", fname);
                setcolor(15);// 15 = WHITE
        } else {
                FILE *fp = NULL;
                
                fp = fopen(fname, "a");
                fclose(fp);
                
                setcolor(14);// 14 = YELLOW
                printf("[mkf] %s\n", fname);
                setcolor(15);//15 = WHITE
        }

}

void make_dir(char *dname) {
        if (mkdir(dname)){
                setcolor(4);
                printf("[mkd] %s already exists, skipping...\n", dname);
                setcolor(15);
        } else {
                setcolor(14);
                printf("[mkd] %s\n", dname);
                setcolor(15);
        }
}

void done(char *text) {
        setcolor(2); // 2 = GREEN
        printf("[%s] DONE\n", text);
        setcolor(15); // 15 = WHITE
}

void announce(char *text){
        setcolor(3);// 3 = CYAN
        puts(text);
        setcolor(15);// 15 = WHITE
}

void setup_node() {
        if (access("package.json", F_OK) == 0) {
                system("npm i");
        } else {
                system("npm init -y");
        }
}

void setup_normal(){
        announce("[NORMAL] START");

        make_dir("assets");
        make_dir("assets/css");
        make_dir("assets/img");
        make_dir("assets/scripts");
        
        done("DIRS");

        make_file("index.html");
        make_file(".env");

        done("FILES");

        announce("[NORMAL] END\n");
}

void setup_express() {
        announce("[EXPRESS] START");

        make_dir("routes");
        make_dir("routes/api");
        make_dir("middleware");
        make_dir("public");
        make_dir("public/images");
        make_dir("public/pages");
        make_dir("public/scripts");
        make_dir("public/styles");

        done("DIRS");

        make_file("routes/index.js");
        make_file("routes/api/index.js");
        make_file("public/index.js");
        make_file("public/pages/404.html");
        make_file("server.js");

        done("FILES");

        announce("[EXPRESS] END\n");
}

void setup_sql() {
        announce("[SQL] START");        

        make_dir("models");
        make_dir("seeds");
        make_dir("db");

        done("DIRS");

        make_file("models/index.js");
        make_file("seeds/seed.js");

        make_file("db/schema.sql");
        make_file("db/seeds.sql");

        done("FILES");

        announce("[SQL] END\n");
}

int main(int argc, char *argv[]){

        int opt;
        int flag = 0; 

        char *usage = "Usage: -n normal, -e express, -q sql";
        
        while((opt = getopt(argc, argv, "nqe")) != -1) {
                switch(opt) {
                        case 'n':
                                system("echo normal");
                                break;
                        case 'q':
                                setup_sql();
                                break;
                        case 'e':
                                setup_express();
                                break;
                        default:
                                fprintf(stderr, usage, argv[0]);
                                exit(EXIT_FAILURE);

                }

                if (opt != -1 && !flag) {
                        flag = 1;
                }
        }
        if(flag) {
            setup_node();
        }

        return 0;
}


