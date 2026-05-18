// WaveFile.cpp
#include "WaveFile.h"
#include <cstring>
#include <cstdio>

namespace
{
	constexpr unsigned int MAINCHUNK_HEADER_SIZE = 8;
	constexpr unsigned int MAINCHUNK_BODY_SIZE = 4;
	constexpr unsigned int SUBCHUNK1_HEADER_SIZE = 8;
	constexpr unsigned int SUBCHUNK1_BODY_SIZE = 16;
	constexpr unsigned int SUBCHUNK2_HEADER_SIZE = 8;
	
	constexpr char RIFF_ID[] = "RIFF";
	constexpr char WAVE_ID[] = "WAVE";
	constexpr char FMT_ID[]  = "fmt ";
	constexpr char DATA_ID[] = "data";
}

bool WriteWaveFile(
	const char* fileName,
	const void* data,
	const unsigned int dataSize,
	const unsigned short numChannels,
	const unsigned int sampleRate,
	const unsigned int bitsPerSample,
	const unsigned short audioFormat = 1)
{
	FILE* file = fopen(fileName, "wb");
	if (!file)
		return false;

	MinimalWaveHeader header{};

	const unsigned int SUBCHUNK2_BODY_SIZE = dataSize;
	const unsigned int bytesPerSample = bitsPerSample / 8;

	header.AudioFormat = audioFormat;
	header.NumChannels = numChannels;
	header.SampleRate = sampleRate;
	header.BitsPerSample = bitsPerSample;

	header.BlockAlign = numChannels * bytesPerSample;
	header.ByteRate = header.BlockAlign * sampleRate;

	header.SubChunk1Size = SUBCHUNK1_BODY_SIZE;
	header.SubChunk2Size = SUBCHUNK2_BODY_SIZE;
	header.ChunkSize =
		MAINCHUNK_BODY_SIZE +
		SUBCHUNK1_HEADER_SIZE + SUBCHUNK1_BODY_SIZE +
		SUBCHUNK2_HEADER_SIZE + SUBCHUNK2_BODY_SIZE;

	memcpy(header.ChunkID,     RIFF_ID, IDWidth);
	memcpy(header.FormatID,    WAVE_ID, IDWidth);
	memcpy(header.SubChunk1ID, FMT_ID,  IDWidth);
	memcpy(header.SubChunk2ID, DATA_ID, IDWidth);

	// write header to file
	fwrite(&header, sizeof(MinimalWaveHeader), 1, file);

	// write data to file
	fwrite(data, dataSize, 1, file);
}
