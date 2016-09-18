#pragma once

int LogManager_write();
//This function will intentionally segfault the program
int LogManager_flush(bool isFlush);
int GameManager_run();