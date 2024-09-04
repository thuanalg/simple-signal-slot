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