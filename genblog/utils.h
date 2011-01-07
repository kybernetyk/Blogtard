#pragma once

extern FILE *fopen_or_die (const char *fname, const char *mode);
extern void append_file_to_fp (const char *filename, FILE *f_out);
extern void append_fp_to_fp (FILE *f_in, FILE *f_out);
extern void append_str_to_fp (const char *str, FILE *f_out);

