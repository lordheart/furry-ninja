#include <stdio.h>
#include <stdlib.h>
#include "track.h"
#include "string.h"

TrackList *newTrackList (AlbumList *al)
{
  TrackList *tl = (TrackList *) malloc (sizeof (TrackList));
  tl->count = 0;
  tl->allocated = 10;
  tl->tracks = (Track **) calloc (tl->allocated, sizeof (Track *));
  tl->albums = al;
  return tl;
}

void deleteTrackList (TrackList *tl)
{
  int i;
  for (i = 0; i < tl->count; i ++)  free (tl->tracks[i]);
  free (tl->tracks);
  free (tl);
}

Track *newTrack (TrackList *tl)
{
  if (tl->count >= tl->allocated)
  { tl->allocated *= 2;
    tl->tracks = (Track **) realloc (tl->tracks, tl->allocated * sizeof (Track *));
  }
  Track *t = (Track *) malloc (sizeof (Track));
  tl->tracks[tl->count++] = t;
  return t;
}

void makeAlbumPointers (TrackList *tl)
{
  int i;
  for (i = 0; i < tl->count; i ++)
    tl->tracks[i]->onAlbum = findAlbum (tl->albums, tl->tracks[i]->albumId);
}

int trackOrder (const void *a, const void *b)
{
  int c;
  Track *ta = *(Track **) a;  Track *tb = *(Track **) b;
  if (a == b) return 0;
  c = strcmp (ta->onAlbum->artist, tb->onAlbum->artist);
  if (c != 0) return c;
  if (ta->onAlbum->year < tb->onAlbum->year) return -1;
  if (ta->onAlbum->year > tb->onAlbum->year) return +1;
  c = strcmp (ta->onAlbum->title, tb->onAlbum->title);
  if (c != 0) return c;
  if (ta->nr < tb->nr) return -1;
  return +1;
}

void sortTrackList (TrackList *tl)
{
  qsort (tl->tracks, tl->count, sizeof (Track *), &trackOrder);
}

void readTrackList (TrackList *tl, char *fileName)
{
  int r, nr;
  FILE *file = fopen (fileName, "r");
  if (file == NULL)  { perror (fileName);  exit (1); }
  do
  {
    r = fscanf (file, "%d", &nr);
    if (r != EOF)
    {
      Track *t = newTrack (tl);
      t->nr = nr;
      r = fscanf (file, "%100s %d", t->title, &t->albumId);
      stringSubst (t->title, '_', ' ');
    }
  }
  while (r != EOF);
  fclose (file);
  makeAlbumPointers (tl);
  sortTrackList (tl);
}

void printTrackList (TrackList *tl)
{
  Album *a = NULL;
  int i;
  for (i = 0; i < tl->count; i ++)
  {
    Track *t = tl->tracks[i];
    if (t->onAlbum != a)
    { a = t->onAlbum;
      printAlbum (a);
    }
    printTrack (t);
  }
}

void printTrack (Track *t)
{
  printf ("  %02d %s\n", t->nr, t->title);
}
