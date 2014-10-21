#include <e2D.h>

tFont::tFont( const char *file, const int &&size ){
  location = file;
  font = assert(TTF_OpenFont(file, size));
};
tFont::~tFont(){
  TTF_CloseFont(font);
}
tFont &tFont::bold(){
  TTF_SetFontStyle(font,TTF_GetFontStyle(font)^TTF_STYLE_BOLD);
  return *this;
};
tFont &tFont::italic(){
  TTF_SetFontStyle(font,TTF_GetFontStyle(font)|TTF_STYLE_ITALIC);
  return *this;
};
tFont &tFont::underline(){
  TTF_SetFontStyle(font,TTF_GetFontStyle(font)|TTF_STYLE_UNDERLINE);
  return *this;
};
tFont &tFont::striked(){
  TTF_SetFontStyle(font,TTF_GetFontStyle(font)|TTF_STYLE_STRIKETHROUGH);
  return *this;
};
tFont &tFont::reset(){
  TTF_SetFontStyle(font,TTF_STYLE_NORMAL);
  TTF_SetFontHinting(font,TTF_HINTING_NONE);
  TTF_SetFontKerning(font,0);
  return *this;
};
tFont &tFont::hinting(){
  TTF_SetFontHinting(font,TTF_HINTING_NORMAL);
  return *this;
};
tFont &tFont::kerning(){
  TTF_SetFontKerning(font,1);
  return *this;
};
tFont &tFont::outline(const int &&outline){
  TTF_SetFontOutline(font, outline);
  return *this;
};

//SDL_Surface *TTF_RenderUTF8_Solid(TTF_Font *font, const char *text, SDL_Color fg)
//int TTF_SizeUTF8(TTF_Font *font, const char *text, int *w, int *h)
