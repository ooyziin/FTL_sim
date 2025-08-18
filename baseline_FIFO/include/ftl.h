#pragma once

int pickVictimBlock();
void migrateValidPage(int src_ppn);
void erase(int bid);
void garbageCollection();
void write_lpn(int lpn);

