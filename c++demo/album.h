#ifndef ALBUM_H
#define ALBUM_H

#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

class EOFException {};

class Album
{
public:
  Album (istream &s)
  { s >> id >> title >> artist >> year;
    if (!s)  throw EOFException ();  // abort constructor!
    replace_if (title.begin (), title.end (), bind2nd (equal_to<char> (), '_'), ' ');
    replace_if (artist.begin (), artist.end (), bind2nd (equal_to<char> (), '_'), ' ');
  }

  Album (unsigned pId) { id = pId; }  // for comparisons

  void print (ostream &o = cout) const
  { o << title << " (" << artist << ", " << year << ")\n"; }

  bool operator< (const Album &a) const  { return id < a.id; }

  bool printOrder (const Album *a) const
  { if (artist < a->artist) return true;
    if (artist > a->artist) return false;
    if (year < a->year) return true;
    if (year > a->year) return false;
    if (title < a->title) return true;
    if (title > a->title) return false;
    return false;
  }

private:
  unsigned id;
  string title, artist;
  unsigned year;
};

inline ostream &operator<< (ostream &o, const Album &a)
{ a.print (o);  return o; }


class AlbumList
{
public:
  AlbumList (char *FileName);
  Album const *findAlbum (unsigned id) const
  { Album a (id); return &*albums.find (a); }
private:
  set<Album> albums;
};

#endif
