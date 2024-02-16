#ifndef OUTPUT_H
#define OUTPUT_H

#include "terminal.h"
#include "linebuf.h"

#define PATH_PARTITION E.screencols/2

#define ESC_SEQ_EXTRA 128

#define SIZE_LABEL "Size"
#define SIZE_LABEL_sz (sizeof(SIZE_LABEL)-1)

#define DATE_PARTITION E.screencols/4
#define DATE_LABEL "Date Mod"
#define DATE_LABEL_sz (sizeof(DATE_LABEL)-1)


void paintStatusBar(struct linebuf *line);

void paintScreen();

#endif
