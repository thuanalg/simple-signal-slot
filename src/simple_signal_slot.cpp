#include "simple_signal_slot.h"
#include <stdio.h>

simple_signal_slot::simple_signal_slot()
{
	fprintf(stdout, "---\n");
}

simple_signal_slot::~simple_signal_slot()
{
	fprintf(stdout, "===========\n");
}

int simple_signal_slot::signal_event(simple_signal_slot *target, generic_data_obj_st *evvt)
{
	int ret = 0;
	fprintf(stdout, "===========\n");
	if (m_implement) {
		ret = m_implement->signal_event(target, evvt);
	}
	return ret;
}

int simple_signal_slot::event_slot(generic_data_obj_st * evvt)
{
	int ret = 0;
	fprintf(stdout, "===========\n");
	if (m_implement) {
		ret = m_implement->event_slot(evvt);
	}
	return ret;
	return 0;
}