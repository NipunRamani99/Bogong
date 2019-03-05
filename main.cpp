
#include "Render.h"
int main()
{		
	Render render;
	render.Start();
	do {
		render.Loop();
	} while (render.KeepRendering);
	render.End();
	return 0;
}
