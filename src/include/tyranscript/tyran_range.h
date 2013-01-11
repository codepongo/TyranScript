#ifndef tyran_range_h
#define tyran_range_h

typedef struct tyran_range {
	int start;
	int end;
} tyran_range;

struct tyran_memory;

tyran_range* tyran_range_new(struct tyran_memory* memory, int start, int end);

#endif
