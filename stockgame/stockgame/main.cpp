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
// TODO: write a script to get thousands of these... for now, just 
//       manually download a few
char* s_fileNames[] =
{
	"..\\Data\\msft.csv",
	"..\\Data\\ge.csv",
};
//-----------------------------------------------------------------------------
static std::vector<StockHistory> s_data;
//-----------------------------------------------------------------------------

void AnalyzeData()
{
	// For many trials...
		// Look at a random 30 day period of a random stock
	
		// Use analytics to determine the predicted stock price at the next day

		// Check the stock price at the next day
	
		// Adjust analytics based on the variance from the predicted outcome
}

//-----------------------------------------------------------------------------
// Main Function
//-----------------------------------------------------------------------------
int main()
{
	// Load files into memory
	LoadFiles(&s_fileNames[0], arrsize(s_fileNames), s_data);

	// Analyze data
	AnalyzeData();

	return 0;
}