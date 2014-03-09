#include "album.h"
#include <fstream>

AlbumList::AlbumList (char *fileName)
{
  ifstream s (fileName);
  try  { for (;;) albums.insert (s); }
  catch (EOFException) {}
}
