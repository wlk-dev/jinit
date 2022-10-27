#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "utils.h"

void setup_node() {
        make_file(".gitignore");
        set_color(fgLIGHTRED, atrSTANDARD);
        if (access("package.json", F_OK) == 0) {
                puts("\nexec : npm i");
                system("npm i");
        } else {
                puts("\nexec : npm init -y");
                system("npm init -y");
        }
        reset_color();
}

void setup_normal(){
        char *dirs[] = {"assets", "assets/css", "assets/imgs", "assets/scripts"};
        char *files[] = {"index.html", ".env"};

        int dlen = sizeofa(dirs);
        int flen = sizeofa(files);
        
        setup(dirs, files, dlen, flen, "NORMAL");

}

void setup_express() {
        char *dirs[] = {"routes", "routes/api", "middleware", "public", "public/images", "public/pages", "public/scripts", "public/styles"};
        char *files[] = {"routes/index.js", "routes/api/index.js", "public/index.js", "public/pages/404.html", "server.js"};

        int dlen = sizeofa(dirs);
        int flen = sizeofa(files);

        setup(dirs, files, dlen, flen, "EXPRESS");
}

void setup_sql() {
        char *dirs[] = {"models", "seeds", "db"};
        char *files[] = {".env", "models/index.js", "seeds/seed.js", "db/schema.sql", "db/seeds.sql"};

        int dlen = sizeofa(dirs);
        int flen = sizeofa(files);

        setup(dirs, files, dlen, flen, "SQL");
}

void setup_mvc() {
        char *dirs[] = {"config", "controllers", "controllers/api" ,"utils", "views", "views/layouts", "views/partials", "public", "public/css", "public/images", "public/js"};
        char *files[] = {"controllers/index.js", "controllers/api/index.js", "controllers/home-routes.js", "config/connection.js"};

        int dlen = sizeofa(dirs);
        int flen = sizeofa(files);

        setup(dirs, files, dlen, flen, "MCV");
}

int main(int argc, char *argv[]){
        int opt;
        int flag = 0; 

        char *usage = "Usage: -n normal, -e express, -q sql, -m mvc";
        
        while((opt = getopt(argc, argv, "nqem")) != -1) {
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
                        case 'm':
                                setup_mvc();
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
        } else {
                printf("%s\n", usage);
        }

        return 0;
}


