/*
==============================================================================

  	Logger.cpp
	Created: 10 Jan 2016 4:27:41pm
	Author:  Jewest
	
This file is part of MIDI2LR. Copyright 2016 by Rory Jaffe.

MIDI2LR is free software: you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later version.

MIDI2LR is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
MIDI2LR.  If not, see <http://www.gnu.org/licenses/>.
==============================================================================
*/
#ifdef _WIN32

#include "Logger.h"
#include <Windows.h>

//constructor
Logger::Logger()
{

}
//destructor
Logger::~Logger()
{
	if (IsOpen())
	{
		//close the file
		Close();
	}
}

void Logger::AddToLog(string &data)
{
	//check if open
	if (!IsOpen())
	{
		//open the log
		Open();
	}

	SYSTEMTIME st;
	GetLocalTime(&st);
	char buffer[100];
	//GetSystemTime(&st);
	//sprintf(buffer, "%d:%02d:%02d %02d:%02d:%02d.%03d:", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
	sprintf(buffer, "%02d:%02d:%02d.%03d: ", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

	m_outStream << buffer;
	m_outStream	<< data ;
	// ensure line
	if (!data.empty())
	{
		if (data.back() != '\n')
		{
			m_outStream << "\n";
		}
	}
	
	// flush to disk.
	m_outStream.flush(); 
	
}

bool Logger::IsOpen(void)
{
	return m_outStream.is_open();

}

void Logger::Open(void)
{
	if (IsOpen())
	{
		Close();
	}

	m_outStream.open(".\\debug.log", std::fstream::out);

}
void Logger::Close(void)
{
	if (IsOpen())
	{
		m_outStream.close();
	}
}

void AddToLog(string newInfo)
{
    static Logger logApp;

	logApp.AddToLog(newInfo);
}
#endif
