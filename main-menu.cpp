#include "libui/ui.h"

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
        return -1;
    }

    uiMenuItem *menuItem;

    uiMenu *menu = uiNewMenu("File");

    menuItem = uiMenuAppendItem(menu, "Open");
    uiMenuItemOnClicked(menuItem, onActionOpen, NULL);

    // uiMenuAppendQuitItem() is the only menuAppend function that triggers an action; the action needs uiOnShouldQuit to be defined and return 1
    menuItem = uiMenuAppendQuitItem(menu);
    uiOnShouldQuit([](void *data){return 1;}, NULL);

    // set the last parameter to 1 if you have a menu
    uiWindow *w = uiNewWindow("Hello", 320, 240, 1);

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

