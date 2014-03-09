#include "album.h"
#include "track.h"

int main (int argc, char *argv[])
{
  if (argc < 3)
  { cerr << "usage: albumlister <albumfile> <trackfile>\n";
    exit (1);
  }
  AlbumList al (argv[1]);
  TrackList tl (argv[2], al);
  cout << tl;
}
