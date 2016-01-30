#pragma once
#include <WinUser.h>
#include <list>
#include <iterator>
using namespace std;

typedef void (*FP1)(void);
typedef void (*FP2)(int n);
typedef void (*FP3)(WPARAM wParam, LPARAM lParam);

class Binding {
public:
	FP1 fp;
	int code;
public:
	Binding(FP1 fp, int code) {
		this->fp = fp;
		this->code = code;
	}

};

class GlobalHooker
{
public:
	static void HookMouse();
	static void UnhookMouse();
	static void HookKeyboard();
	static void UnhookKeyboard();

	static void addKeyPressHandler(FP1 fp, int nKeyCode);
	static void addKeyDownHandler(FP1 fp, int nKeyCode);
	static void addKeyUpHandler(FP1 fp, int nKeyCode);

	static FP1 OnKeyboadEvent;
	static FP2 OnKeyPress;
	static FP2 OnKeyDown;
	static FP2 OnKeyUp;

	static FP3 OnMouseEvent;
	static FP1 OnLButtonDown;
	static FP1 OnRButtonDown;

	
	static list<Binding> keyPressHandlers;
	static list<Binding> keyDownHandlers;
	static list<Binding> keyUpHandlers;

private:
	static HHOOK hMouseHook;
	static HHOOK hKeyboadHook;
	


};

