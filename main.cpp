#include "libui/ui.h"

int main()
{
    // @todo: is this correct?
	uiInitOptions o = {0};
	// memset(&o, 0, sizeof (uiInitOptions)); like above, but setting 0 everywere
	if (uiInit(&o) != NULL) {
        return -1;
    }

    // set the last parameter to 1 if you have a menu
    uiWindow *w = uiNewWindow("Hello World", 320, 240, 0);

	uiBox *b =uiNewVerticalBox();
    uiBoxSetPadded(b, 1);
    uiWindowSetChild(w, uiControl(b));

    uiButton *btn = uiNewButton("Quit");
    uiButtonOnClicked(btn, [](uiButton *b, void *data){uiQuit();}, NULL);
    uiBoxAppend(b, uiControl(btn), 0);

    // quit the application when the window closes
	uiWindowOnClosing(w, [](uiWindow *w, void *data) {uiQuit(); return 1;}, NULL);

    uiControlShow(uiControl(w));
    uiMain();
}
