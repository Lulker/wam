#include "Map.hh"
#include <cstdio>

char *freadall(const char *file){
    FILE *f = fopen(file, "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *string = new char[fsize + 1];
    fread(string, fsize, 1, f);
    fclose(f);
    string[fsize] = 0;
    return string;
}

int getint(char *&str){
    int num = 0;
    for(;*str>('0'-1) && *str<('9'+1);++str)
        num = (num*10) + (int)(*str-'0');
    return num;
}

Map::Map(const char *file){
    char * c = freadall(file);
    char * d = c;
    do{while(*++c!='<');} while (*++c!='l' || *++c!='a' || *++c!='y' || *++c!='e' || *++c!='r');
    do{while(*++c!='w');} while (*++c!='i' || *++c!='d' || *++c!='t' || *++c!='h' || *++c!='=' || *++c!='"');
    width = getint(++c);
    do{while(*++c!='h');} while (*++c!='e' || *++c!='i' || *++c!='g' || *++c!='h' || *++c!='t' || *++c!='=' || *++c!='"');
    height = getint(++c);
    int size = width*height;
    for(;;){
        do{
            while(*++c!='c')
                if(!*c)
                    goto end;
        } while (*++c!='s' || *++c!='v' || *++c!='"' || *++c!='>');
        int * layer = new int[size];
        ++c;
        for(int i=0; i<size; ++i){
            for(;*c==','||*c=='\n'||*c=='\r';++c);
            layer[i] = getint(c)-1;
        }
        layers.push_back(layer);
    }
    end: delete[] d;
}
