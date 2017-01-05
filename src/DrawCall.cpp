#include "DrawCall.h"
#include <iostream>

void DrawElementsConfig::execute() const {
	glDrawElements(mode, count, type, indices);
}

DrawElementsInstancedConfig DrawElementsConfig::to_instanced() const {
	return DrawElementsInstancedConfig(mode, count, 1, type, indices);
}

void DrawArraysConfig::execute() const {
	glDrawArrays(mode, first, count);
}

DrawArraysInstancedConfig DrawArraysConfig::to_instanced() const {
	return DrawArraysInstancedConfig(mode, count, 1, first);
}

void DrawElementsInstancedConfig::execute() const {
	glDrawElementsInstanced(mode, count, type, indices, primCount);
}

DrawElementsConfig DrawElementsInstancedConfig::to_single() const {
	return DrawElementsConfig(mode, count, type, indices);
}

void DrawArraysInstancedConfig::execute() const {
	glDrawArraysInstanced(mode, first, count, primCount);
}

DrawArraysConfig DrawArraysInstancedConfig::to_single() const {
	return DrawArraysConfig(mode, count, first);
}
