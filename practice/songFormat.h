#ifndef SONGFORMAT_H
#define SONGFORMAT_H

enum SongFormat { MP3, FLAC, AAC, OGG, WAV };

static constexpr int NUM_EXTENSIONS = 5;
static const char* SongExtensions[NUM_EXTENSIONS] = {".mp3", ".flac", ".aac", ".ogg", ".wav"};

#endif // !SONGFORMAT_H
