#ifndef _TYRAN_OPCODE_ENUMS_H
#define _TYRAN_OPCODE_ENUMS_H

enum tyran_resolve_type {
	tyran_resolve_continue,
	tyran_resolve_break
};

enum tyran_shift_mode {
	tyran_shift_left,
	tyran_shift_right,
	tyran_shift_right_unsigned
};

enum tyran_assign_mode {
	tyran_assign_variable,
	tyran_assign_object
};

enum tyran_subscript_mode {
	tyran_subscript_write,
	tyran_subscript_read
};

#endif
