#ifndef ALBUM_H
#define ALBUM_H

typedef struct
{
  int id;
  char title[101];
  char artist[101];
  int year;
} Album;

typedef struct
{
  Album **albums;
  int count;
  int allocated;
} AlbumList;

AlbumList *newAlbumList ();
void deleteAlbumList (AlbumList *al);
Album *newAlbum (AlbumList *al);
void readAlbumList (AlbumList *al, char *fileName);
Album *findAlbum (AlbumList *al, int id);
void printAlbum (Album *a);

void stringSubst (char *s, char old, char new);  // gehört eigtl. nicht hierher

#endif
