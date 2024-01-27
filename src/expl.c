	#include <stdlib.h>
	#include <unistd.h>
	#include <string.h>

	#include "expl.h"
	#include "terminal.h"
	#include "userinput.h"
	#include "ansi_escape_codes.h"
	#include "output.h"
	#include "linebuf.h"
	#include "dirio.h"

	struct exploreConfig E;

	struct linebuf **lines;

	void cleanUp() {

		for(int i = 0 ; i < E.screenrows ; i++) {
			lbFree(lines[i]);
		}
		free(lines);
		free(E.path);
		writeOut(END_ALT_TERM_BUF , END_ALT_TERM_BUF_l);
		disableRawMode();
	}

	void die (const char *s) {
		cleanUp();
		write(ERROR , s , strlen(s));
		exit(1);
	}

	int main() {

		enableRawMode();

		writeOut(INIT_ALT_TERM_BUF MV_CURS_HOME , INIT_ALT_TERM_BUF_l + MV_CURS_HOME_l);

		if(getCurrentDir() == -1) die("getCurrentDir");
		if(getWindowSize(&E.screenrows , &E.screencols) == -1) die("WindowSize");

		lines = malloc(E.screenrows * sizeof(struct linebuf*));
		if(lines == NULL) die("malloc(lines)");

		for(int i = 0 ; i < E.screenrows ; i++) {
			lines[i] = lbAllocate(E.screencols + ESC_SEQ_EXTRA);
		}

		paintScreen();

		while(1) {
			processKeypress();
		}

		return 0;
	}
