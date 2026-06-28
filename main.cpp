// main.cpp
#pragma once
#include "WaveFile.h"

void basicMonoSawtooth() {
	int sampleRate = 44100;
	int numSeconds = 5;
	int numChannels = 1;

	int numSamples = sampleRate * numSeconds * numChannels;
	int* dataPtr = new int[numSamples] {};

	int value = 0;
	for (int i = 0 ; i < numSamples ; i++) {
		value += 4000000;
		dataPtr[i] = value;
	}

	WriteWaveFile(
		"sawmono.wav",
		dataPtr,
		numSamples * sizeof(dataPtr[0]),
		numChannels,
		sampleRate,
		sizeof(dataPtr[0]) * 8
	);

	delete dataPtr;
}

void basicStereoSawtooth() {	
	int sampleRate = 44100;
	int numSeconds = 5;
	int numChannels = 2;

	int numSamples = sampleRate * numSeconds * numChannels;
	int* dataPtr = new int[numSamples] {};

	int value1 = 0;
	int value2 = 0;
	for (int i = 0 ; i < numSamples ; i += 2) {
		value1 += 4000000;
		value2 += 600000;
		dataPtr[i]     = value1;
		dataPtr[i + 1] = value2;
	}

	WriteWaveFile(
		"sawstereo.wav",
		dataPtr,
		numSamples * sizeof(dataPtr[0]),
		numChannels,
		sampleRate,
		sizeof(dataPtr[0]) * 8
	);

	delete dataPtr;
}

int main() {

	basicMonoSawtooth();
	basicStereoSawtooth();
	return 0;
}
