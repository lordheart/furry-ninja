#include <stdio.h>
#include <stdlib.h>
#include "album.h"

AlbumList *newAlbumList ()
{
  AlbumList *al = (AlbumList *) malloc (sizeof (AlbumList));
  al->count = 0;
  al->allocated = 10;
  al->albums = (Album **) calloc (al->allocated, sizeof (Album *));
  return al;
}

void deleteAlbumList (AlbumList *al)
{
  int i;
  for (i = 0; i < al->count; i ++)  free (al->albums[i]);
  free (al->albums);
  free (al);
}

Album *newAlbum (AlbumList *al)
{
  if (al->count >= al->allocated)
  { al->allocated *= 2;
    al->albums = (Album **) realloc (al->albums, al->allocated * sizeof (Album *));
  }
  Album *a = (Album *) malloc (sizeof (Album));
  al->albums[al->count++] = a;
  return a;
}

void readAlbumList (AlbumList *al, char *fileName)
{
  FILE *file = fopen (fileName, "r");
  if (file == NULL)  { perror (fileName);  exit (1); }
  int r, id;
  do
  {
    r = fscanf (file, "%d", &id);
    if (r != EOF)
    {
      Album *a = newAlbum (al);
      a->id = id;
      r = fscanf (file, "%100s %100s %d", a->title, a->artist, &a->year);
      stringSubst (a->title, '_', ' ');
      stringSubst (a->artist, '_', ' ');
    }
  }
  while (r != EOF);
  fclose (file);
}

Album *findAlbum (AlbumList *al, int id)
{
  int i;
  for (i = 0; i < al->count; i ++)
    if (al->albums[i]->id == id)
      return (al->albums[i]);
  fprintf (stderr, "Album Id %d not found\n", id);
  exit (1);
}

void printAlbum (Album *a)
{
  printf ("%s (%s, %d)\n", a->title, a->artist, a->year);
}

void stringSubst (char *s, char old, char new)
{
  while (*s) { if (*s == old) *s = new; s ++; }
}
