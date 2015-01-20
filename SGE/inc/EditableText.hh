#include "GEK.hh"
#include "UI.hh"
#include "uSDL.hh"
//TODO:NOTWORKING
struct EditableText : UI {
    bool changed;
    bool active;
    std::string inputText = "";
    std::function<void(const eK_Event & e)> textinput;
    std::function<void(const eK_Event & e)> keydown;
    std::function<void(const eK_Event & e)>* scene_textinput;
    std::function<void(const eK_Event & e)>* scene_keydown;
    public:
        static eK_TTF *font;
        EditableText():texture(0),changed(0),active(0){
            keydown = [&](const eK_Event & e){
                changed = true;
                if( e.key.keysym.sym == '\b' && inputText.length() > 0 )
                    inputText.pop_back();
                else if( e.key.keysym.sym == 'c' && SDL_GetModState() & KMOD_CTRL )
                    SDL_SetClipboardText( &inputText[0] );
                else if( e.key.keysym.sym == 'v' && SDL_GetModState() & KMOD_CTRL )
                    inputText = SDL_GetClipboardText();
            };
            textinput = [&](const eK_Event & e){
                changed = true;
                if(!active || (( e.text.text[ 0 ] == 'c' || e.text.text[ 0 ] == 'C' ) && ( e.text.text[ 0 ] == 'v' || e.text.text[ 0 ] == 'V' ) && SDL_GetModState() & KMOD_CTRL )) return;
                inputText += e.text.text;
            };
        }
        void draw(){
            if(changed){
                auto surface = TTF_RenderText_Solid(font,str,{255,255,255,255})
                if(surface)
                texture = GEK::text(inputText);
                changed = false;
            }
            if(texture)
                SDL_RenderCopyEx(GEK::renderer, texture, 0, &destination, 0, 0, 0);
            if( (GEK::mouse.updated & Mouse::L) && (GEK::mouse.status & Mouse::L)){
                if((active = contains(GEK::mouse.position))){
                    SDL_StartTextInput();
                    *scene_textinput = textinput;
                    *scene_keydown = keydown;
                } else
                    SDL_StopTextInput();
            }
        }
}
