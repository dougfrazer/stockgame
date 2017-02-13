#pragma once

#include <assert.h>
#include <vector>

#define arrsize(x) (sizeof(x) / sizeof(*x))

struct StockDay {
	char date[256]; // mostly just used for debugging
	float open;
	float high;
	float low;
	float close;
	float volume;
};
typedef std::vector<StockDay> StockHistory;