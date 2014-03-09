#include "album.h"

typedef struct
{
  int nr;
  char title[101];
  int albumId;
  Album *onAlbum;
} Track;

typedef struct
{
  Track **tracks;
  int count;
  int allocated;
  AlbumList *albums;
} TrackList;

TrackList *newTrackList (AlbumList *al);
void deleteTrackList (TrackList *tl);
Track *newTrack (TrackList *tl);
void readTrackList (TrackList *tl, char *fileName);
void printTrackList (TrackList *tl);
void printTrack (Track *t);
