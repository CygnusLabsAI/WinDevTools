#pragma once

// WinDevTools includes a feature that allows you to easily keep track of the window objects created
// within the framework. All abstract window classes (e.g. AWindow[W/A], AChildWindow[W/A], etc.) contain
// conditionals that will automatically map a pointer to those abstract class objects to the Windows HWND
// handle associated with that particular window object. In order to utilize this feature, simply add
// "#define WDT_USE_WINDOW_MGMT" which will declare: std::map<HWND, AWindow*> sg_WindowMap for the 
// framework (or you, if you desire) to utilize. You can further control what type of windows will be 
// added to the map by defining WDT_MANAGE_ALL or any of WDT_MANAGE_PARENT, WDT_MANAGE_CHILD, 
// WDT_MANAGE_POPUP, and WDT_MANAGE_CONTROL.
// 
// IMPORTANT NOTE: If you derive a class from any of the framework classes and opt NOT to call the
// base class constructors in the derived class' constructor, but still want to utilize the window
// object management feature, you can manually add the derived class object using the
// WDT_SET_USERDEFINED() macro with a pointer to the derived class object.
//
// A Note about WDT_MANAGE_CONTROL: Many predefined window classes (e.g. "EDIT", "STATIC", "BUTTON",
// etc.) send their parent window messages depending on if certain styles are chosen. If
// WDT_MANAGE_CONTROL is defined, these specific messages are rerouted back to virtual handlers
// of the AControlWindow[W/A] class, so that you may provide custom handling of these control specific
// messages within your control class. This feature was provided as a quality of life improvement
// over complex and hard to read/write Window Procedures, by keeping with the framework design of
// simplifying the process of writing a windows application.

#define WDT_USE_WINDOW_MGMT
#define WDT_MANAGE_ALL

#ifdef WDT_USE_WINDOW_MGMT
	#include <Windows.h>
	#include <map>
	#include "AWindow.h"
	static std::map<HWND, WinDevTools::GUI::AWindow*> sg_WindowMap;
	#define WDT_SET_WND(p) sg_WindowMap[p->getHandle()] = p
	#define WDT_SET_USERDEFINED(p) WDT_SET_WND((WinDevTools::GUI::AWindow*)p)
	
	#ifdef WDT_MANAGE_ALL
		#define WDT_PARENT_MGMT true
		#define WDT_CHILD_MGMT true
		#define WDT_POPUP_MGMT true
		#define WDT_CONTROL_MGMT true
	#else
		#ifdef WDT_MANAGE_PARENT
			#define WDT_PARENT_MGMT true
		#else
			#define WDT_PARENT_MGMT false
		#endif // WDT_MANAGE_PARENT
		#ifdef WDT_MANAGE_CHILD
			#define WDT_CHILD_MGMT true
		#else
			#define WDT_CHILD_MGMT false
		#endif // WDT_MANAGE_CHILD
		#ifdef WDT_MANAGE_POPUP
			#define WDT_POPUP_MGMT true
		#else
			#define WDT_POPUP_MGMT false
		#endif // WDT_MANAGE_POPUP
		#ifdef WDT_MANAGE_CONTROL
			#define WDT_CONTROL_MGMT true
		#else
			#define WDT_CONTROL_MGMT false
		#endif // WDT_MANAGE_CONTROL
	#endif // WDT_MANAGE_ALL
#else
	#define WDT_SET_USERDEFINED(p)
	#define WDT_PARENT_MGMT false
	#define WDT_CHILD_MGMT false
	#define WDT_POPUP_MGMT false
	#define WDT_CONTROL_MGMT false
#endif // WDT_USE_WINDOW_MGMT

#if WDT_PARENT_MGMT true
	#define WDT_SET_PARENT(p) WDT_SET_WND(p)
#else
	#define WDT_ADD_PARENT(p)
#endif // WDT_PARENT_MGMT true

#if WDT_CHILD_MGMT true
	#define WDT_SET_CHILD(p) WDT_SET_WND(p)
#else
	#define WDT_SET_CHILD(p)
#endif // WDT_CHILD_MGMT true

#if WDT_POPUP_MGMT true
	#define WDT_SET_POPUP(p) WDT_SET_WND(p)
#else
	#define WDT_ADD_POPUP(p)
#endif // WDT_POPUP_MGMT true

#if WDT_CONTROL_MGMT true
	#define WDT_SET_CONTROL(p) WDT_SET_WND(p)
#else
	#define WDT_SET_CONTROL(p)
#endif // WDT_CONTROL_MGMT true