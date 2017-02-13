#include "analyzer.h"

#include <Windows.h>
#include <random>

//-----------------------------------------------------------------------------
struct Weight {
public:
	Weight()
		: numSamples(0)
		, total(0.0f)
#ifdef _DEBUG
		, avg(0.0f)
#endif
	{
	}
	void AddSample(float v) {
		total += v;
		numSamples += 1;
#ifdef _DEBUG
		avg = total / numSamples;
#endif
	}
	float GetAverage()
	{
		return total / numSamples;
	}
private:
	int numSamples;
	float total;
#ifdef _DEBUG
	float avg;
#endif
};
//-----------------------------------------------------------------------------
const int NUM_DAYS_TO_ANALYZE = 30;
Weight s_weights[NUM_DAYS_TO_ANALYZE];
//-----------------------------------------------------------------------------
void AnalyzeData(const std::vector<StockHistory>& data)
{
	// For many trials...
	const int NUM_TRIALS = 10000;
	for (int trial = 0; trial < NUM_TRIALS; trial++) {
		// Look at a random NUM_DAYS_TO_ANALYZE day period of a random stock
		int stockNum = rand() % data.size();
		auto& stock = data[stockNum];
		int dayNum = rand() % stock.size();
		const int startDay = dayNum;
		int predictionDayIndex = min(startDay + NUM_DAYS_TO_ANALYZE + 1, stock.size() - 1);
		auto& predictionDay = stock[predictionDayIndex];

		// Compute a moving average based on the variance from the prediction day
		dayNum = startDay;
		while (dayNum < predictionDayIndex - 1) {
			s_weights[dayNum - startDay].AddSample((stock[dayNum].close - predictionDay.close) / (stock[dayNum].close));
			dayNum++;
		}

		// Compute the 'predicted value'... which for now is just the weighted sum
		float sum = 0.0f;
		dayNum = startDay;
		while (dayNum < predictionDayIndex - 1) {
			sum += stock[dayNum].close * 1.0f + s_weights[dayNum - startDay].GetAverage();
			dayNum++;
		}
		float predictedNextDay = sum / (dayNum - startDay);

		// Check the stock price at the next day
		float variance = (predictedNextDay - predictionDay.close);
		char buffer[2048];
		sprintf_s(buffer, 2048, "Trial %d: variance: %.2f\n", trial, variance);
		OutputDebugString(buffer);
	}
}