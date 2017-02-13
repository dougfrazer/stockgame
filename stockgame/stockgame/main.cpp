#include "defs.h"
#include "parser.h"
#include "analyzer.h"


//-----------------------------------------------------------------------------
// Static Data
//-----------------------------------------------------------------------------
// TODO: write a script to get thousands of these... for now, just 
//       manually download a few
char* s_fileNames[] =
{
	"..\\Data\\msft.csv",
	"..\\Data\\ge.csv",
	"..\\Data\\intc.csv",
	"..\\Data\\f.csv",
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
	AnalyzeData(s_data);

	return 0;
}