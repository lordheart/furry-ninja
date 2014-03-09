#include "album.h"
#include "track.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
  if (argc < 3)
  { fputs ("usage: albumlister <albumfile> <trackfile>\n", stderr);
    exit (1);
  }
  AlbumList *al = newAlbumList ();
  readAlbumList (al, argv[1]);
  TrackList *tl = newTrackList (al);
  readTrackList (tl, argv[2]);
  printTrackList (tl);
  deleteAlbumList (al);
  deleteTrackList (tl);
  return 0;
}
