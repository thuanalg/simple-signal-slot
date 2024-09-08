#include "simple_implement_signal_slot.h"
#include <stdio.h>
#ifndef UNIX_LINUX
	#include <windows.h>
#else
#endif

/*===============================================================================================================*/
/* Email:
*		<nguyenthaithuanalg@gmail.com> - Nguyễn Thái Thuận
* Mobile:
*		<+084.799.324.179>
* Skype:
*		<nguyenthaithuanalg>
* Date:
*		<2024-Sep-04>
* The lasted modified date:
*		<2024-Sep-09>
* Decription:
*		TODO
*/
/*===============================================================================================================*/
/*
#ifndef UNIX_LINUX
#else
#endif
*/
static void* spl_signal_slot_create_sem();
static void* spl_signal_slot_create_mutex();
static DWORD WINAPI simple_implement_signal_slot_wait_for_event_loop(LPVOID lpParam);
void* spl_signal_slot_create_sem() {
	void* ret = 0;
	do {
#ifndef UNIX_LINUX
		HANDLE hd = 0;
		hd = CreateSemaphoreA(0, 0, 1, 0);
		if (!hd) {
			//Log error
			break;
		}
		ret = hd;
#else

#endif
	} while (0);
	return ret;
}
void* spl_signal_slot_create_mutex() {
	void* ret = 0;
	do {
#ifndef UNIX_LINUX
		HANDLE hd = 0;
		hd = CreateMutexA(0, 0, 0);
		if (!hd) {
			//Log error
			break;
		}
		ret = hd;
#else

#endif
	} while (0);
	return ret;
}
simple_implement_signal_slot::simple_implement_signal_slot()
{
	m_sem = m_mutex = 0;
	m_looper = 0;
	do {
		m_sem = spl_signal_slot_create_sem();
		if (!m_sem) {
			break;
		}
		m_mutex = spl_signal_slot_create_mutex();
		if (!m_mutex) {
			break;
		}
		m_looper = this;
		generate_event_thread(this);
	} while (0);
	fprintf(stdout, "---\n");
}

simple_implement_signal_slot::simple_implement_signal_slot(simple_signal_slot* looper)
{
	//m_eventList.clear();
	m_looper = looper;
	m_looper = 0;
	m_sem = m_mutex = 0;
	fprintf(stdout, "---\n");
}

simple_implement_signal_slot::~simple_implement_signal_slot()
{
	//m_eventList.clear();
	fprintf(stdout, "===========\n");
}

int simple_implement_signal_slot::signal_event(simple_signal_slot *target, generic_data_obj_st * evennt)
{
	int ret = 0;
	ZZZZZZ obj = { 0, 0 };
	obj.target = target;
	obj.evt = evennt;
	return ret;
}


int simple_implement_signal_slot::event_slot(generic_data_obj_st * evvt)
{
	int ret = 0;

	return ret;
}


void simple_implement_signal_slot::GetClassCurrentName(std::string& str)
{
	str.clear();
	str = "simple_implement_signal_slot";
}

int simple_implement_signal_slot::generate_event_thread(void* arg)
{
	do {
#ifndef UNIX_LINUX
		HANDLE hd = 0;
		DWORD thid = 0;
		hd = CreateThread(0, 0, simple_implement_signal_slot_wait_for_event_loop, arg, 0, &thid);
#else
#endif
	} while (0);
	return 0;
}

DWORD WINAPI 
simple_implement_signal_slot_wait_for_event_loop
(LPVOID arg)
{
	int ret = 0;
	simple_implement_signal_slot* obj = (simple_implement_signal_slot*) arg;
	std::vector<ZZZZZZ> currentEvents;
	ZZZZZZ* tmp = 0;
	simple_signal_slot* target = 0;
	while (1)
	{
		//Wait for semaphore here
		//Mutex here
		currentEvents = obj->m_eventList;
		obj->m_eventList.clear();
		//Mutex clock here
		while (1) {
			//Fetch event loop
			if (!tmp) {
				break;
			}
			target = (simple_signal_slot*)tmp->target;
			if (!target) {
				//Error here
			}
			//Call virtual function to process.
			target->event_slot(tmp->evt);
			free(tmp->evt);
		}
	}
	return ret;
}