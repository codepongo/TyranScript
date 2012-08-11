#ifndef _TYRAN_LABEL_H
#define _TYRAN_LABEL_H

struct tyran_string;

typedef struct tyran_label {
	const struct tyran_string* name;
	int position;
} tyran_label;

#endif
