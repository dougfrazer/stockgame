#include <stdio.h>
#include <vector>
#include <Windows.h>
#include <string>
#include <assert.h>

#include "defs.h"
#include "parser.h"

//-----------------------------------------------------------------------------
// Static Data
//-----------------------------------------------------------------------------
char* s_fileNames[] =
{
	"..\\Data\\msft.csv",
	"..\\Data\\ge.csv",
};
//-----------------------------------------------------------------------------
static std::vector<StockHistory> s_data;
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Main Function
//-----------------------------------------------------------------------------
int main()
{
	// Load files into memory
	LoadFiles(&s_fileNames[0], arrsize(s_fileNames), s_data);

	// Analyze data
	// TODO

	return 0;
}