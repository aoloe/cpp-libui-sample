#include "libui/ui.h"

int onWindowClosing(uiWindow *w, void *data)
{
	uiQuit();
	return 1;
}

void onActionOpen(uiMenuItem *item, uiWindow *mainwin, void *data)
{
	char *filename;

	filename = uiOpenFile(mainwin);
	if (filename == NULL) {
		uiMsgBoxError(mainwin, "No file selected", "Don't be alarmed!");
		return;
	}
	uiMsgBox(mainwin, "File selected", filename);
	uiFreeText(filename);
}

void onActionQuit(uiMenuItem *item, uiWindow *w, void *data)
{
    uiQuit();
}


int main()
{
	uiInitOptions o = {0};
	// memset(&o, 0, sizeof (uiInitOptions)); like above, but setting 0 everywere
	if (uiInit(&o) != NULL) {
		// abort();
        return -1;
    }

    uiMenuItem *menuItem;

    uiMenu *menu = uiNewMenu("File");
    menuItem = uiMenuAppendItem(menu, "Open");
	uiMenuItemOnClicked(menuItem, onActionOpen, NULL);
    // menuItem = uiMenuAppendItem(menu, "Quit");
	// uiMenuItemOnClicked(menuItem, onActionQuit, NULL);
	menuItem = uiMenuAppendQuitItem(menu);
	// uiOnShouldQuit(onActionQuit, NULL);
	uiOnShouldQuit([](void *data){return 1;}, NULL); // uiMenuAppendQuitItem() is the only menuAppend function that triggers an action; the action needs uiOnShouldQuit to be defined and return 1

    // uiWindow *w = uiNewWindow("Hello", 320, 240, 0); // set the last parameter to 0 if you have a menu
    uiWindow *w = uiNewWindow("Hello", 320, 240, 1); // set the last parameter to 1 if you have a menu

	uiBox *b =uiNewVerticalBox();
    uiBoxSetPadded(b, 1);
    uiWindowSetChild(w, uiControl(b));

    uiButton *btn = uiNewButton("Quit");
    uiButtonOnClicked(btn, [](uiButton *b, void *data){uiQuit();}, NULL);
    uiBoxAppend(b, uiControl(btn), 0);

	uiWindowOnClosing(w, onWindowClosing, NULL);
	// uiWindowOnClosing(w, [](uiWindow *w, void *data) {uiQuit(); return 1;}, NULL);

    uiControlShow(uiControl(w));
    uiMain();
}
