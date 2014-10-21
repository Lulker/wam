#pragma once
#include <eK.h>

class tFont
{
	private:
		const char *location;
		TTF_Font *font;
	public:
		tFont( const char *file, const int &&size );
		~tFont();
		tFont &bold();
		tFont &italic();
		tFont &underline();
		tFont &striked();
		tFont &reset();
		tFont &hinting();
		tFont &kerning();
		tFont &outline(const int &&outline);
};
