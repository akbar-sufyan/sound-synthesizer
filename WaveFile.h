// WaveFile.h
#pragma once

constexpr int IDWidth = 4;

struct MinimalWaveHeader
{
	// main chunk
	unsigned char ChunkID[IDWidth];		// "RIFF"
	unsigned int ChunkSize;
	unsigned char FormatID[IDWidth];	// "WAVE"

	// sub chunk 1
	unsigned char SubChunk1ID[IDWidth];	// "fmt"
	unsigned int SubChunk1Size;
	unsigned short AudioFormat;
	unsigned short NumChannels;
	unsigned int SampleRate;
	unsigned int ByteRate;
	unsigned short BlockAlign;
	unsigned short BitsPerSample;

	// sub chunk 2
	unsigned char SubChunk2ID[IDWidth];	// "data"
	unsigned int SubChunk2Size;

	// then comes the data
};

bool WriteWaveFile(
	const char* fileName,
	const void* data,
	const unsigned int dataSize,
	const unsigned short numChannels,
	const unsigned int sampleRate,
	const unsigned int bitsPerSample,
	const unsigned short audioFormat = 1);
