#include "track.h"
#include <fstream>

TrackList::TrackList (char *fileName, AlbumList &al)
: albums (al)
{
  ifstream s (fileName);
  try  { for (;;) tracks.push_back (s); }
  catch (EOFException) {}
  for (unsigned i = 0; i < tracks.size (); i ++)
    tracks[i].lookupAlbum (al);
}

struct TrackOrder
{ bool operator() (const Track *a, const Track *b) const
  { return *a < *b; }
};

void TrackList::print (ostream &o) const
{
  set<const Track *, TrackOrder> ts;
  for (unsigned i = 0; i < tracks.size (); i ++)
    ts.insert (&tracks[i]);
  const Album *a = 0;
  for (set<const Track *, TrackOrder>::iterator i = ts.begin (); i != ts.end (); i ++)
  { if ((*i)->getAlbum () != a)
    { a = (*i)->getAlbum ();  o << *a; }
    o << **i;
  }
}
