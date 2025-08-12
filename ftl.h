#pragma once
#include <string>
#include "ssd_config.h"

int  pickVictimBlock();
void migrateValidPage(int src_ppn);
void erase(int bid);
void garbageCollection();
void write_lpn(int lpn);
