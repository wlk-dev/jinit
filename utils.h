#include <stdio.h>
#include <Windows.h>

#define sizeofa(array) sizeof array / sizeof array[ 0 ]

void setcolor(int color) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void done(char *text) {
        setcolor(2); // 2 = GREEN
        printf("[%s] DONE\n", text);
        setcolor(15); // 15 = WHITE
}

void announce(char *exec, char *indicator){
        setcolor(3);// 3 = CYAN
        printf("[%s] %s\n", exec, indicator);
        setcolor(15);// 15 = WHITE
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


void setup(char *dirs[], char *files[], int dlen, int flen, char *name) {
        announce(name, "START");

        for(int i = 0; i < dlen; i++) {
                make_dir(dirs[i]);
        }

        done("DIRS");
        

        for(int i = 0; i < flen; i++) {
                make_file(files[i]);
        }
        
        done("FILES");
        announce(name, "END");
}


