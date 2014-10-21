int tilewidth;
int tileheight;
int width;
int height;
std::vector<std::vector<int>> Layers;

int getint(char *& str){
  int num;
  for(;;++c)
    if(*c>('0'-1) && *c<('9'+1))
      num = (num*10) + (int)(*c-'0');
  return num;
}

int getuntil(char *& str, char t){
  char *end;
  while(*++end!='"');
    end = 0;

}

void eMap::eMap( , const char* filename, ssize_t offset ){
  do{
    while(*++c!='t');
  } while (*++c!='i' || *++c!='l' || *++c!='e' || *++c!='w' || *++c!='i' || *++c!='d' || *++c!='t' || *++c!='h' || *++c!='=');
  tilewidth = getint(c);
  do{
    while(*++c!='t');
  } while (*++c!='i' || *++c!='l' || *++c!='e' || *++c!='h' || *++c!='e' || *++c!='i' || *++c!='g' || *++c!='h' || *++c!='t' || *++c!='=');
  tileheight = getint(c);
  for(;;){
    do{
      while(*++c!='s')
        if(c[0]=='<' && c[1]=='/' && c[2]=='t' && c[3]=='i' && c[4]=='l' && c[5]=='e' && c[6]=='s')
          goto end;
    } while (*++c!='o' || *++c!='u' || *++c!='r' || *++c!='c' || *++c!='e' || *++c!='=' );
    //LOAD TILE
  }
  end:
  do{
    while(*++c!='<');
  } while (*++c!='l' || *++c!='a' || *++c!='y' || *++c!='e' || *++c!='r');
  do{
    while(*++c!='w');
  } while (*++c!='i' || *++c!='d' || *++c!='t' || *++c!='h' || *++c!='=' || *++c!='"');
  width = getint();
  do{
    while(*++c!='h');
  } while (*++c!='e' || *++c!='i' || *++c!='g' || *++c!='h' || *++c!='t' || *++c!='=' || *++c!='"');
  height = getint();

  for(;;){
    do{
      while(*++c!='c')
        if(!*c)
          return;
    } while (*++c!='s' || *++c!='v' || *++c!='"' || *++c!='>');

    while(*c!='<' && *c!=0)
      getint()
  }
}
