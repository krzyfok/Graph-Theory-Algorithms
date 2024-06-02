#pragma once
class LicznikCzasu {
public:
	void start();
	double stop();
	double PCFreq = 0.0;
	__int64 CounterStart = 0;

};
extern LicznikCzasu licznik;