#include <stdio.h>
#include <string.h>


struct state_file_record_int
{
	char fmt[8];
	char name[30];
	int value;
};


// some helpers there

FILE* create_state_file(const char* filename) {
	FILE *file = fopen(filename, "wb");
	if (file) {
		return file;
	}
	// TODO: handle error there ?
	return NULL;
}

int close_state_file(FILE *file) {
	return fclose(file);
}

// helpers end


int write_to_state_file(FILE *file, struct state_file_record_int inc_struct) {
	int res;
	memset(inc_struct.fmt, 0, 8);
	strcpy(inc_struct.fmt, "30sI");  // set the format there
	res = fwrite(&inc_struct, sizeof inc_struct, 1, file);
	fflush(file);
	return res;
}


int write_uwsgi_state(FILE *file, int state) {
	struct state_file_record_int inc_struct;
	inc_struct.value = state;
	memset(inc_struct.name, 0, 30);
	strcpy(inc_struct.name, "UWSGI_STATE");
	return write_to_state_file(file, inc_struct);
}
