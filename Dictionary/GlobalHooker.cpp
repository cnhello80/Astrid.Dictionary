#include "stdafx.h"
#include "GlobalHooker.h"
#include <Windows.h>

LRESULT CALLBACK  MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK  KeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam);

void GlobalHooker::addKeyDownHandler(FP1 fp, int vkCode) {
	Binding binding(fp, vkCode);
	GlobalHooker::keyDownHandlers.push_back(binding);
}

void GlobalHooker::addKeyUpHandler(FP1 fp, int vkCode) {
	Binding binding(fp, vkCode);
	GlobalHooker::keyUpHandlers.push_back(binding);
}

void GlobalHooker::addKeyPressHandler(FP1 fp, int vkCode) {
	Binding binding(fp, vkCode);
	GlobalHooker::keyPressHandlers.push_back(binding);
}

void GlobalHooker::HookMouse() {
	hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseHookProc, 0, 0);
}
void GlobalHooker::UnhookMouse() {
	bool success = UnhookWindowsHookEx(hMouseHook);
	if (!success)
	{
		;
	}
}
void GlobalHooker::HookKeyboard(){
	hKeyboadHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHookProc, 0, 0);
}
void GlobalHooker::UnhookKeyboard() {
	bool success = UnhookWindowsHookEx(hKeyboadHook);
	if (!success)
	{
		;
	}
}
FP1 GlobalHooker::OnKeyboadEvent;
FP2 GlobalHooker::OnKeyPress;
FP2 GlobalHooker::OnKeyDown;
FP2 GlobalHooker::OnKeyUp;
FP3 GlobalHooker::OnMouseEvent;
FP1 GlobalHooker::OnLButtonDown;
FP1 GlobalHooker::OnRButtonDown;
HHOOK GlobalHooker::hMouseHook;
HHOOK GlobalHooker::hKeyboadHook;
list<Binding> GlobalHooker::keyPressHandlers = list<Binding>();
list<Binding> GlobalHooker::keyDownHandlers = list<Binding>();
list<Binding> GlobalHooker::keyUpHandlers = list<Binding>();




static void iter(list<Binding>& bindings, int vkCode) {
	if (bindings.size() == 0) {
		return;
	}
	for (list<Binding>::iterator i = bindings.begin(); i != GlobalHooker::keyDownHandlers.end(); i++)
	{
		if ((*i).code == vkCode)
		{
			(*i).fp();
		}
	}
}
LRESULT CALLBACK  MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam) {

	if (nCode >= 0 )
	{
		switch (wParam)
		{
		case WM_LBUTTONDOWN:
			if (GlobalHooker::OnLButtonDown != NULL)
			{
				GlobalHooker::OnLButtonDown();
			}
			break;
		case WM_RBUTTONDOWN:
			if (GlobalHooker::OnRButtonDown != NULL)
			{
				GlobalHooker::OnRButtonDown();
			}
			break;
		default:
			break;
		}
		if (GlobalHooker::OnMouseEvent != NULL)
		{
			GlobalHooker::OnMouseEvent(wParam, lParam);
		}
	}

	return CallNextHookEx(0, nCode, wParam, lParam);
}
LRESULT CALLBACK  KeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam) {

	int vkCode = ((int*)lParam)[0];
	if (nCode >= 0)
	{
		switch (wParam)
		{
		case WM_KEYDOWN:
			if (GlobalHooker::OnKeyDown != NULL)
			{
				GlobalHooker::OnKeyDown(vkCode);
			}
			iter(GlobalHooker::keyDownHandlers, vkCode);

			break;
		case WM_KEYUP:
			if (GlobalHooker::OnKeyUp != NULL)
			{
				GlobalHooker::OnKeyUp(vkCode);
			}
			iter(GlobalHooker::keyUpHandlers, vkCode);
			break;
		case DISPID_KEYPRESS:
			if (GlobalHooker::OnKeyPress != NULL)
			{
				GlobalHooker::OnKeyPress(((int*)lParam)[0]);
			}
			iter(GlobalHooker::keyPressHandlers, vkCode);
			break;
		default:
			break;
		}
	}

	return CallNextHookEx(0, nCode, wParam, lParam);
}



