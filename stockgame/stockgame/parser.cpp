#include "parser.h"

#include "defs.h"
#include <Windows.h>

class CSVIterator
{
public:
	CSVIterator(char* _buffer, int _fileSize, int startIndex, int endIndex)
		: m_buffer(_buffer)
		, m_fileSize(_fileSize)
		, m_startIndex(startIndex)
		, m_endIndex(endIndex)
	{
	}

	CSVIterator& operator++()
	{
		m_startIndex = m_endIndex + 1;
		m_endIndex = m_startIndex;
		while (m_buffer[m_endIndex] != ',' && m_buffer[m_endIndex] != '\n' && m_endIndex < m_fileSize) {
			assert(m_endIndex - m_startIndex < MAX_RETURN_SIZE);
			m_endIndex++;
		}
		return *this;
	}

	char* operator*()
	{
		if (m_startIndex == -1) {
			return *(++*this); // special case for the very first time...
		}
		ZeroMemory(&m_return[0], MAX_RETURN_SIZE);
		memcpy(&m_return[0], &m_buffer[m_startIndex], m_endIndex - m_startIndex);
		return &m_return[0];
	}

	bool operator == (const CSVIterator& rhs)
	{
		const bool dataMatches = m_buffer == rhs.m_buffer && m_fileSize == rhs.m_fileSize;
		const bool endIndexMatches = m_endIndex == rhs.m_endIndex;

		return dataMatches && endIndexMatches;
	}
	bool operator != (const CSVIterator& rhs) { return !(*this == rhs); }

private:
	char* m_buffer;
	int   m_fileSize;
	int   m_startIndex;
	int   m_endIndex;
	static const int MAX_RETURN_SIZE = 256;
	char  m_return[MAX_RETURN_SIZE];
};
//-----------------------------------------------------------------------------
class CSV
{
public:
	CSV(char* buffer, int fileSize)
		: m_buffer(buffer)
		, m_fileSize(fileSize)
	{}

	CSVIterator begin()
	{
		return CSVIterator(m_buffer, m_fileSize, -1, -1);
	}

	CSVIterator end()
	{
		return CSVIterator(m_buffer, m_fileSize, -1, m_fileSize);
	}
private:
	char* m_buffer;
	int   m_fileSize;
};
//-----------------------------------------------------------------------------
static void ParseFile(char* buffer, int fileSize, StockHistory &outData)
{
	CSV csv = CSV(buffer, fileSize);
	int headerCount = 0;
	int index = 0;
	enum COLUMNS {
		DATE,
		OPEN,
		HIGH,
		LOW,
		CLOSE,
		VOLUME,

		NUM_COLUMNS,
	};
	StockDay data;
	for (char* string : csv) {
		// Skip past the header
		if (headerCount < NUM_COLUMNS) {
			headerCount++;
			continue;
		}

		switch ((COLUMNS)index)
		{
		case DATE:
			strcpy_s(data.date, 256, string);
			break;
		case OPEN:
			data.open = atof(string);
			break;
		case HIGH:
			data.high = atof(string);
			break;
		case LOW:
			data.low = atof(string);
			break;
		case CLOSE:
			data.close = atof(string);
			break;
		case VOLUME:
			data.volume = atof(string);
			break;
		}

		index++;
		if (index == NUM_COLUMNS) {
			outData.push_back(data);
			index = 0;
		}
	}
	assert(index == 0); // something is probably wrong if we only got a partial row
}
//-----------------------------------------------------------------------------
void LoadFiles(char** fileList, int fileCount, std::vector<StockHistory>& outHistory)
{
	for (int i = 0; i < fileCount; i++) {
		char* fileName = fileList[i];
		FILE* file = nullptr;
		fopen_s(&file, fileName, "rb");
		if (!file) {
			return;
		}

		fseek(file, 0L, SEEK_END);
		int fileSize = ftell(file);
		rewind(file);

		char* readBuffer = (char*)malloc(fileSize);
		if (fread(readBuffer, 1, fileSize, file) != fileSize) {
			return;
		}

		StockHistory history;
		ParseFile(readBuffer, fileSize, history);
		outHistory.push_back(history);

		free(readBuffer);
		fclose(file);
	}
}