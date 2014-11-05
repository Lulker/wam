#include <string>
#include <unistd.h>
#include <SGE.hpp>

using namespace SGE;

class sStart : public Scene
{
	public:
	void init(){};//GEK::scene = new sGame;};
};

SGE_Main(new sStart)
