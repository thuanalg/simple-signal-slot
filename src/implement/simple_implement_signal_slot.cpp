#include "simple_implement_signal_slot.h"
#include "simplelog.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#ifndef UNIX_LINUX
	#include <windows.h>
#else
	#include <pthread.h>
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
*		<2024-Dec-06>
* Decription:
*		TODO
*/
/*===============================================================================================================*/
/*
#ifndef UNIX_LINUX
#else
#endif
*/
#define ss_malloc(__nn__, __obj__, __type__) { (__obj__) = (__type__*) malloc(__nn__); if(__obj__) \
	{spllog(0, "Malloc: 0x%p\n", (__obj__)); memset((__obj__), 0, (__nn__));} \
	else {spllog(0, "Malloc: error.\n");}} 

#ifndef UNIX_LINUX
#include <windows.h>
#else

#define ss_pthread_mutex_lock(__obj, __err) \
		{ (__err) = pthread_mutex_lock((pthread_mutex_t*)(__obj)); if((__err)) spllog(0, "pthread_mutex_lock errcode: %d. %s\n", (__err), (__err) ? "FALIED": "DONE");}

#define ss_pthread_mutex_unlock(__obj, __err) \
		{ (__err) = pthread_mutex_unlock((pthread_mutex_t*)(__obj)); if((__err)) spllog(0, "pthread_mutex_unlock errcode: %d. %s\n", (__err), (__err) ? "FALIED": "DONE");}

#define ss_sem_wait(__obj) \
		sem_wait((sem_t*)(__obj))

#define ss_sem_post(__obj) \
		sem_post((sem_t*)(__obj))
#endif
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
static void*
	ss_mutex_create();
static int
	ss_mutex_unlock(void* obj);
static int 
	ss_mutex_lock(void* obj);

static void*
	ss_sem_create(int ini);
static 
	int ss_sem_post(void* obj);
static 
	int ss_sem_wait(void* obj);

static DWORD WINAPI simple_implement_signal_slot_wait_for_event_loop(LPVOID lpParam);
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
int simple_implement_signal_slot::initial() {
	
	do {
		m_sem = ss_sem_create(1);
		if (!m_sem) {
			break;
		}
		m_mutex = ss_mutex_create();
		if (!m_mutex) {
			break;
		}
	} while (0);
	m_looper = this;
	return 0;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
simple_implement_signal_slot::simple_implement_signal_slot(simple_signal_slot* looper, std::string &name)
{
	spllog(SPL_LOG_BASE, "0x:%p, looper: 0x:%p", this, looper);
	this->m_name = name;
	if (!looper) {
		initial();
		generate_event_thread(this);
	}
	else {
		simple_implement_signal_slot* obj = (simple_implement_signal_slot*)looper->m_implement;
		simple_implement_signal_slot* loopper = (simple_implement_signal_slot*)obj->m_looper;
		m_looper = obj->m_looper;
		m_sem = m_mutex = 0;
		m_curentThread = loopper->m_curentThread;
	}
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
simple_implement_signal_slot::~simple_implement_signal_slot()
{
	spllog(SPL_LOG_BASE, "0x:%p", this);
	if (m_sem) {
		CloseHandle((HANDLE)m_sem);
		m_sem = 0;
	}
	if (m_mutex) {
		CloseHandle((HANDLE)m_mutex);
		m_mutex = 0;
	}
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
int simple_implement_signal_slot::signal_event(simple_signal_slot* src, simple_signal_slot *target, generic_data_obj_st * evennt)
{
	int ret = 0;
	simple_implement_signal_slot* p = 0;
	simple_implement_signal_slot* looper = 0;
	do {
		SS_EVENT_ST *obj = 0;
		//obj = (SS_EVENT_ST*) malloc(sizeof(SS_EVENT_ST));
		ss_malloc(sizeof(SS_EVENT_ST), obj, SS_EVENT_ST);
		if (!obj) {
			break;
		}
		obj->evt = evennt;
		obj->target = target;
		obj->src = src;
		if (!target) {
			break;
		}
		p = (simple_implement_signal_slot*)target->m_implement;
		looper = (simple_implement_signal_slot*)p->m_looper;
		if (!p->m_looper) {
			break;
		}
		ss_mutex_lock(looper->m_mutex);
		if (1) {
			looper->m_eventList.push_back(obj);
		}
		ss_mutex_unlock(looper->m_mutex);
		ss_sem_post(looper->m_sem);
	} while (0);
	return ret;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

int simple_implement_signal_slot::event_slot(generic_data_obj_st * evvt)
{
	int ret = 0;

	return ret;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void simple_implement_signal_slot::GetClassCurrentName(std::string& str)
{
	str.clear();
	str = "simple_implement_signal_slot";
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
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
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
DWORD WINAPI 
simple_implement_signal_slot_wait_for_event_loop
(LPVOID arg)
{
	int ret = 0;
	simple_implement_signal_slot* obj = (simple_implement_signal_slot*) arg;
	simple_implement_signal_slot* obj_impl = 0;
	std::vector<SS_EVENT_ST *> currentEvents;
	SS_EVENT_ST* tmp = 0;
	simple_signal_slot* target = 0;
	HANDLE semaphore = (HANDLE)obj->m_sem;
	int isstop = 0;
	obj->m_curentThread = (LLU)ss_get_threadid();
	while (1)
	{
		if (!semaphore) {
			break;
		}
		WaitForSingleObject(semaphore, INFINITE);
		spllog(SPL_LOG_BASE, "Enter event loop.");
		ss_mutex_lock(obj->m_mutex);
		if (1) {
			currentEvents = obj->m_eventList;
			obj->m_eventList.clear();
		}
		ss_mutex_unlock(obj->m_mutex);
		while (1) {
			
			//Fetch event loop
			if (currentEvents.size() < 1) {
				break;
			}
			tmp = currentEvents.front();
			if (!tmp) {
				break;
			}
			currentEvents.erase(currentEvents.begin());
			target = (simple_signal_slot*)tmp->target;
			if (!target) {
				break;
			}
			obj_impl = (simple_implement_signal_slot*)target->m_implement;
			if (tmp->evt->in_main_thread) {
				spllog(SPL_LOG_BASE, "in_main_thread.");
				target->AccessMainThread(tmp->evt);
			}
			else {
				spllog(SPL_LOG_BASE, "Diff main thread.");
				target->event_slot(tmp->evt);
				if (tmp->evt->ss_event_id == SS_EVENT_STOP) {
					isstop = 1;
				}
				free(tmp->evt);
			}
			//Call virtual function to process.
			free(tmp);
			tmp = 0;
		}
		if (isstop) {
			break;
		}
	}
	spllog(SPL_LOG_BASE, "End event loop.");
	return ret;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
int ss_mutex_lock(void* obj) {
	int ret = 0;
#ifndef UNIX_LINUX
	DWORD err = 0;
#else
#endif	
	do {
		if (!obj) {
			ret = SS_ERROR_MUTEX_NULL;
			break;
		}
#ifndef UNIX_LINUX
		err = WaitForSingleObject(obj, INFINITE);
		if (err != WAIT_OBJECT_0) {
			ret = 1;
			break;
		}
#else
		ss_pthread_mutex_lock((pthread_mutex_t*)obj, ret);
#endif
	} while (0);
	return ret;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

int ss_mutex_unlock(void* obj) {
	int ret = 0;
#ifndef UNIX_LINUX
	DWORD done = 0;
#else
#endif	
	do {
		if (!obj) {
			ret = SS_ERROR_MUTEX_NULL;
			break;
		}
#ifndef UNIX_LINUX
		done = ReleaseMutex(obj);
		if (!done) {
			ret = 1;
			break;
		}
#else
		ss_pthread_mutex_unlock((pthread_mutex_t*)obj, ret);
#endif
	} while (0);
	return ret;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void simple_implement_signal_slot::SetName(const std::string& name) {
	m_name = name;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void simple_implement_signal_slot::GetName(std::string& name) {
	name = m_name;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

LLU	ss_get_threadid() {
#ifndef UNIX_LINUX
	return (LLU)GetCurrentThreadId();
#else
	return (LLU)pthread_self();
#endif
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
int ss_sem_post(void* sem) {
	int ret = 0;
	do {
#ifndef UNIX_LINUX
		ret = ReleaseSemaphore((HANDLE)sem, 1, 0);
		if (ret) {
			ret = 0;
		}
		else {
			ret = (int)GetLastError();
		}
#else
		ret = ss_sem_post(sem);
#endif
	} while (0);
	return ret;
}
int ss_sem_wait(void* obj) {
	int ret = 0;
	do {
#ifndef UNIX_LINUX
		ret = (int)WaitForSingleObject((HANDLE)obj, INFINITE);
#else
		ret = ss_sem_wait(obj);
#endif
	} while (0);
	return ret;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void* ss_sem_create(int ini) {
	void* ret = 0;
	do {
#ifndef UNIX_LINUX
		ret = CreateSemaphoreA(0, 0, ini, 0);
#else
		ss_malloc(sizeof(sem_t), ret, void);
		if (!ret) {
			break;
		}
		memset(ret, 0, sizeof(sem_t));
		sem_init((sem_t*)ret, 0, 0);
#endif 
	} while (0);
	return ret;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void* ss_mutex_create() {
	void* ret = 0;
	do {
#ifndef UNIX_LINUX
		ret = CreateMutexA(0, 0, 0);
#else
		/*https://linux.die.net/man/3/pthread_mutex_init*/
		spl_malloc(sizeof(pthread_mutex_t), ret, void);
		if (!ret) {
			break;
		}
		memset(ret, 0, sizeof(pthread_mutex_t));
		pthread_mutex_init((pthread_mutex_t*)ret, 0);
#endif 
	} while (0);
	return ret;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+