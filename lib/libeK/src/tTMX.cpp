#include <eK.hpp>
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

void tTMX::camera(int layer0, int layer, float x, float y, int Ax, int Ay){
  float drawx = (x-(long)x)*-tilewidth;
  float drawy = (y-(long)y)*-tileheight;
  xo = x-Ax;
  yo = y-Ay;
  int x0 = ((long)x)-Ax;
  int y0 = ((long)y)-Ay;
  Ax = (x0+(Ax<<1)>width)?width-x0:Ax<<1;
  Ay = (y0+(Ay<<1)>height)?height-y0:Ay<<1;
  for(int l=layer0;l<layer;++l)
    for(int j=(y0<0)?-y0:0;j<Ay;++j)
      for(int i=(x0<0)?-x0:0;i<Ax;++i)
        tileset[layers[l][(x0+i)+((y0+j)*width)]]->draw(drawx+(tilewidth*i),drawy+(tileheight*j));
}

float tTMX::xraycast(const int &x){
  return xo+((float)x/(float)tilewidth);
}

float tTMX::yraycast(const int &y){
  return yo+((float)y/(float)tileheight);
}

float tTMX::xtracecast(const float &x){
  return (x-xo)*tilewidth;
}

float tTMX::ytracecast(const float &y){
  return (y-yo)*tileheight;
}

tTMX::~tTMX(){
  for(auto& tile : tileset)
    delete tile;
  tileset.clear();
  for(auto& layer : layers)
    delete[] layer;
  layers.clear();
};

tTMX::tTMX(const char *file, eK &ek, const int &offset){
  char * c = freadall(file);
  char * d = c;
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
    tileset.push_back(ek.sprite(getuntil(c,'"')+offset));
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
  int size = width*height;
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
