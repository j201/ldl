#include <math.h>
#include <stdlib.h>
#include "lv2/lv2plug.in/ns/lv2core/lv2.h"
#define LDL_URI "http://j201.github.io/plugins/ldl"

typedef enum {
	INPUT = 0,
	OUTPUT
} Port;

typedef struct {
	const float* input;
	float*       output;
} LDL;

static LV2_Handle instantiate(
		const LV2_Descriptor* desc,
		double rate,
		const char* path,
		const LV2_Feature* const* features
		) {

	return calloc(1, sizeof(LDL));
}

static void connect_port(LV2_Handle inst, uint32_t port, void* data) {
	LDL* ldl = (LDL*)inst;

	switch ((Port)port) {
	case INPUT:
		ldl->input = (const float*)data;
		break;
	case OUTPUT:
		ldl->output = (float*)data;
		break;
	}
}

static void activate(LV2_Handle instance) {
}

static void run(LV2_Handle inst, uint32_t nsamp) {
	const LDL* ldl = (const LDL*)inst;

	for (int i = 0; i < nsamp; i++) {
		ldl->output[i] = ldl->input[i];
	}
}

static void deactivate(LV2_Handle instance) {
}

static void cleanup(LV2_Handle inst) {
	free(inst);
}

static const void* extension_data(const char* uri) {
	return NULL;
}

static const LV2_Descriptor descriptor = {
	LDL_URI,
	instantiate,
	connect_port,
	activate,
	run,
	deactivate,
	cleanup,
	extension_data
};

LV2_SYMBOL_EXPORT const LV2_Descriptor* lv2_descriptor(uint32_t i) {
	if (i == 0) {
		return &descriptor;
	}
	return NULL;
}
