#ifndef AUDIOPROPERTIES_H
#define AUDIOPROPERTIES_H

class AudioProperties
{
public:
	AudioProperties()
		:bitrate(0), channels(0), length(0), lengthMilliseconds(0), sampleRate(0)
	{}

	AudioProperties(int br, int ch, int len, int lenms, int sr)
		:bitrate(br), channels(ch), length(len), lengthMilliseconds(lenms), sampleRate(sr)
	{}

	template <class Archive>
	void save(Archive& archive) const
	{
		archive(bitrate, channels, length, lengthMilliseconds, sampleRate);
	}

	template <class Archive>
	void load(Archive& archive)
	{
		archive(bitrate, channels, length, lengthMilliseconds, sampleRate);
	}

	unsigned int bitrate;
	unsigned int channels;
	unsigned int length;
	unsigned int lengthMilliseconds;
	unsigned int sampleRate;

};

#endif // !AUDIOPROPERTIES_H
