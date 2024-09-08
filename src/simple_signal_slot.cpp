﻿#include "simple_signal_slot.h"
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
*		<2024-Sep-05>
* Decription:
*		TODO
*/
/*===============================================================================================================*/
/*
#ifndef UNIX_LINUX
#else
#endif
*/
simple_signal_slot::simple_signal_slot()
{
	m_implement = new simple_implement_signal_slot();
	fprintf(stdout, "---\n");
}

simple_signal_slot::simple_signal_slot(simple_signal_slot *looper)
{
	m_implement = new simple_implement_signal_slot(looper);
	fprintf(stdout, "---\n");
}

simple_signal_slot::~simple_signal_slot()
{
	if (m_implement) {
		delete(m_implement);
		m_implement = 0;
	}
	fprintf(stdout, "===========\n");
}

int simple_signal_slot::signal_event(simple_signal_slot *target, generic_data_obj_st *evvt)
{
	int ret = 0;
	fprintf(stdout, "===========\n");
	simple_implement_signal_slot* obj = (simple_implement_signal_slot*)m_implement;
	if (obj) {
		ret = obj->signal_event(target, evvt);
	}
	return ret;
}

int simple_signal_slot::event_slot(generic_data_obj_st * evvt)
{
	int ret = 0;

	return ret;
}

void simple_signal_slot::GetClassCurrentName(std::string& str)
{
	str.clear();
	str = "simple_signal_slot";
}

void simple_signal_slot::Init_MainthreadID()
{
#ifndef UNIX_LINUX
	simple_signal_slot::m_MainthreadID = (LLU)GetCurrentThreadId();
#else
#endif
}

LLU simple_signal_slot::m_MainthreadID = 0;