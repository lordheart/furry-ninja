#include <iostream>
#include <vector>
#include <algorithm>
#include "album.h"
#include <iomanip>

using namespace std;

class Track
{
public:
  Track (istream &s)
  { s >> nr >> title >> albumId;
    if (!s)  throw EOFException ();  // abort constructor!
    replace_if (title.begin (), title.end (), bind2nd (equal_to<char> (), '_'), ' ');
  }

  void print (ostream &o = cout) const
  { o << "  " << setw (2) << setfill ('0') << nr << ' ' << title << endl; }

  void lookupAlbum (AlbumList &al)
  { onAlbum = al.findAlbum (albumId); }

  bool operator< (const Track &t) const
  { if (onAlbum->printOrder (t.onAlbum)) return true;
    if (t.onAlbum->printOrder (onAlbum)) return false;
    return nr < t.nr;
  }

  const Album *getAlbum () const  { return onAlbum; }

private:
  unsigned nr;
  string title;
  unsigned albumId;
  const Album *onAlbum;
};

inline ostream &operator<< (ostream &o, const Track &t)
{ t.print (o);  return o; }


class TrackList
{
public:
  TrackList (char *fileName, AlbumList &al);
  void print (ostream &o = cout) const;
private:
  vector<Track> tracks;
  AlbumList &albums;
};

inline ostream &operator<< (ostream &o, const TrackList &tl)
{ tl.print (o);  return o; }
