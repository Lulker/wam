#include <eK.h>

char * freadall(const char * filename){
  FILE *f = fopen(filename, "rb");
  fseek(f, 0, SEEK_END);
  long fsize = ftell(f);
  fseek(f, 0, SEEK_SET);

  char *string = new char[fsize + 1];
  fread(string, fsize, 1, f);
  fclose(f);
  string[fsize] = 0;
  return string;
}

int getint(char *& str){
  int num = 0;
  for(;*str>('0'-1) && *str<('9'+1);++str)
    num = (num*10) + (int)(*str-'0');
  return num;
}

char * getuntil(char *& str, char t){
  char * start = &(*str);
  while(*++str!=t);
  *str = 0;
  ++str;
  return start;
}

void tTMX::draw(int layer, int x0, int x, int y0, int y, float drawx0, float drawy0){
  int Ax = (x>width)?width-x0:x-x0;
  int Ay = (y>height)?height-y0:y-y0;
  for(int i=(x0<0)?-x0:0;i<Ax;++i)
    for(int j=(y0<0)?-y0:0;j<Ay;++j)
        tileset[layers[layer][(x0+i)+((y0+j)*width)]]->draw(drawx0+(tilewidth*i),drawy0+(tileheight*j));
}

tTMX::tTMX( const char * filename, SDL_Renderer * ren , const int & offset ){
  char * c = freadall(filename);
  do{
    while(*++c!='t');
  } while (*++c!='i' || *++c!='l' || *++c!='e' || *++c!='w' || *++c!='i' || *++c!='d' || *++c!='t' || *++c!='h' || *++c!='=' || *++c!='"');
  tilewidth = getint(++c);
  do{
    while(*++c!='t');
  } while (*++c!='i' || *++c!='l' || *++c!='e' || *++c!='h' || *++c!='e' || *++c!='i' || *++c!='g' || *++c!='h' || *++c!='t' || *++c!='=' || *++c!='"');
  tileheight = getint(++c);
  for(;;){
    do{
      while(*++c!='s')
        if(c[0]=='<' && c[1]=='/' && c[2]=='t' && c[3]=='i' && c[4]=='l' && c[5]=='e' && c[6]=='s')
          goto end;
    } while (*++c!='o' || *++c!='u' || *++c!='r' || *++c!='c' || *++c!='e' || *++c!='=' || *++c!='"');
    tileset.push_back(new tSprite(getuntil(c,'"')+4,ren));
  }
  end:
  do{
    while(*++c!='<');
  } while (*++c!='l' || *++c!='a' || *++c!='y' || *++c!='e' || *++c!='r');
  do{
    while(*++c!='w');
  } while (*++c!='i' || *++c!='d' || *++c!='t' || *++c!='h' || *++c!='=' || *++c!='"');
  width = getint(++c);
  do{
    while(*++c!='h');
  } while (*++c!='e' || *++c!='i' || *++c!='g' || *++c!='h' || *++c!='t' || *++c!='=' || *++c!='"');
  height = getint(++c);
  size = width*height;
  for(;;){
    do{
      while(*++c!='c'){
        if(!*c)
          return;
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
