#include <stdio.h>
#include <stdlib.h>
#include "termcolors.h"

#define sizeofa(array) sizeof array / sizeof array[ 0 ]

void reset_color(){
        //system(" ");
        printf("\e(B\e[m");

}

void set_color(int foreground) {
        system(" ");
        printf("\e[3;%dm", foreground);
}


void done(char *text) {
        set_color(fgGREEN); 
        printf("[%s] DONE\n", text);
}

void announce(char *exec, char *indicator){
        set_color(fgCYAN); 
        printf("[%s] %s\n", exec, indicator);
}

void make_file(char *fname) {
        if (access(fname, F_OK) == 0) {
                system(" "); 
                printf("\e[1;31m[mkf] %s already exists, skipping...\n", fname);
        } else {
                FILE *fp = NULL;
                
                fp = fopen(fname, "a");
                fclose(fp);
        
                set_color(fgYELLOW);
                printf("[mkf] %s\n", fname);
        }

        reset_color();
}

void make_dir(char *dname) {
        if (mkdir(dname)){
                set_color(fgYELLOW);
                printf("[mkd] %s already exists, skipping...\n", dname);
        } else {
                set_color(fgYELLOW);
                printf("[mkd] %s\n", dname);
        }
        reset_color();
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


