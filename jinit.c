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
        char *dirs[] = {"assets", "assets/css", "assets/imgs", "assets/scripts"};
        char *files[] = {"index.html", ".env"};

        int dlen = sizeof(dirs)/sizeof(dirs[0]);
        int flen = sizeof(files)/sizeof(files[0]);

        announce("[NORMAL] START");

        for(int i = 0; i < dlen; i++) {
                make_dir(dirs[i]);
        }

        done("DIRS");
        

        for(int i = 0; i < flen; i++) {
                make_file(files[i]);
        }
        
        done("FILES");
        announce("[NORMAL] END\n");
}

void setup_express() {
        char *dirs[] = {"routes", "routes/api", "middleware", "public", "public/images", "public/pages", "public/scripts", "public/styles"};
        char *files[] = {"routes/index.js", "routes/api/index.js", "public/index.js", "public/pages/404.html", "server.js"};

        int dlen = sizeof(dirs)/sizeof(dirs[0]);
        int flen = sizeof(files)/sizeof(files[0]);

        announce("[EXPRESS] START");

        for(int i = 0; i < dlen; i++) {
                make_dir(dirs[i]);
        }

        done("DIRS");
        

        for(int i = 0; i < flen; i++) {
                make_file(files[i]);
        }
        
        done("FILES");
        
        announce("[EXPRESS] END");

}

void setup_sql() {
        char *dirs[] = {"models", "seeds", "db"};
        char *files[] = {"models/index.js", "seeds/seed.js", "db/schema.sql", "db/seeds.sql"};

        int dlen = sizeof(dirs)/sizeof(dirs[0]);
        int flen = sizeof(files)/sizeof(files[0]);

        announce("[SQL] START");

        for(int i = 0; i < dlen; i++) {
                make_dir(dirs[i]);
        }

        done("DIRS");
        

        for(int i = 0; i < flen; i++) {
                make_file(files[i]);
        }
        
        done("FILES");
        
        announce("[SQL] END");
}

int main(int argc, char *argv[]){

        int opt;
        int flag = 0; 

        char *usage = "Usage: -n normal, -e express, -q sql";
        
        while((opt = getopt(argc, argv, "nqe")) != -1) {
                switch(opt) {
                        case 'n':
                                setup_normal();
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


