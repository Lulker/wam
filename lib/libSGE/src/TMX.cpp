#include <SGE.hpp>
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

char *getuntil(char *&str, char t){
	char * start = &(*str);
	while(*++str!=t);
	*str = 0;
	++str;
	return start;
}

SGE::TMX::~TMX(){
	puts("TMX destructing");
	for(auto& tile : tileset)
		delete tile;
	tileset.clear();
	for(auto& layer : layers)
		delete[] layer;
	layers.clear();
debug(snafu)}

SGE::TMX::TMX(const char *file, const int &offset){
	char * c = freadall(file);
	char * d = c;
	do{
		while(*++c!='t');
	} while (*++c!='i' || *++c!='l' || *++c!='e' || *++c!='w' || *++c!='i' || *++c!='d' || *++c!='t' || *++c!='h' || *++c!='=' || *++c!='"');
	tile.x = getint(++c);
	do{
		while(*++c!='t');
	} while (*++c!='i' || *++c!='l' || *++c!='e' || *++c!='h' || *++c!='e' || *++c!='i' || *++c!='g' || *++c!='h' || *++c!='t' || *++c!='=' || *++c!='"');
	tile.y = getint(++c);
	for(;;){
		do{
			while(*++c!='s')
				if(c[0]=='<' && c[1]=='/' && c[2]=='t' && c[3]=='i' && c[4]=='l' && c[5]=='e' && c[6]=='s')
					goto end;
		} while (*++c!='o' || *++c!='u' || *++c!='r' || *++c!='c' || *++c!='e' || *++c!='=' || *++c!='"');
		tileset.push_back(new Sprite(Surface(getuntil(c,'"')+offset)));
	}
	end:
	do{
		while(*++c!='<');
	} while (*++c!='l' || *++c!='a' || *++c!='y' || *++c!='e' || *++c!='r');
	do{
		while(*++c!='w');
	} while (*++c!='i' || *++c!='d' || *++c!='t' || *++c!='h' || *++c!='=' || *++c!='"');
	map.x = getint(++c);
	do{
		while(*++c!='h');
	} while (*++c!='e' || *++c!='i' || *++c!='g' || *++c!='h' || *++c!='t' || *++c!='=' || *++c!='"');
	map.y = getint(++c);
	int size = map.x*map.y;
	for(;;){
		do{
			while(*++c!='c'){
				if(!*c){
					delete[] d;
					return;
				}
			}
		} while (*++c!='s' || *++c!='v' || *++c!='"' || *++c!='>');
		int * layer = new int[size];
		++c;
		for(int i=0; i<size; ++i){
			for(;*c==','||*c=='\n'||*c=='\r';++c);
			layer[i] = getint(c)-1;
		}
		layers.push_back(layer);
	}
}
