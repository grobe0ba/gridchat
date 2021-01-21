#include <u.h>
#include <libc.h>
#include <bio.h>
#include <stdio.h>

#define LINELEN 80

const Rune sep = L'→';

void fatal(char *s) {
	sysfatal(s);
}

int main(void) {
	Biobuf *i;
	Biobuf *o;
	char *line;
	char *tok;
	int toklen;
	char *idx;
	int nicklen;
	int linelen;
	int j;
	int f;

	i = Bfdopen(0, OREAD);
	o = Bfdopen(1, OWRITE);
	
	Blethal(i, fatal);
	Blethal(o, fatal);
	
	while((line = Brdstr(i, '\n', 1)) != nil) {
		f = 1;
		linelen = 0;
		tok = line;
		toklen = 0;
		while((tok = strtok(tok, " ")) != 0) {
			toklen = strlen(tok);
			if (f) {
				nicklen = toklen;
				linelen = nicklen + 2;
				f = 0;
			}
			if (linelen + toklen + 1 > LINELEN) {
				Bputc(o, '\n');
				for(j = 0; j <= nicklen + 2; ++j, Bwrite(o, " ", 1));
				linelen = nicklen + 3;
			}
			Bwrite(o, tok, toklen);
			Bwrite(o, " ", 1);
			linelen += toklen + 1;
			tok = nil;
		}
		Bwrite(o, "\n", 1);
	}
	Bterm(i);
	Bterm(o);

	return 0;
}
