/*
 * Exercise 16: http://c.learncodethehardway.org/
 *
 * Use pointers and structs to implement file-backed catalogue system.
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512
#define MAX_ROWS 200

struct Address {
  int id;
  int set;
  char name[MAX_DATA];
  char email[MAX_DATA];
};

struct Database {
  struct Address rows[MAX_ROWS];
};

struct Connection {
  FILE *file;
  struct Database *db;
};

void die(const char *message)
{
  if (errno) {
    perror(message);
  } else {
    printf("Fehler:%s\n", message);
  }

  exit(1);
}

void Address_print(struct Address *addr)
{
  printf("%d, %s %s\n", addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn)
{
  int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);

  if(rc != 1) die("Shits happened with the file");
}

struct Connection *Database_open(const char *filename, char mode)
{
  char *err_msg = "Memory shits, boys!";

  struct Connection *conn = malloc(sizeof(struct Connection));
  if (!conn) die(err_msg);

  conn->db = malloc(sizeof(struct Database));
  if (!conn->db) die(err_msg);

  if (mode == 'c') {
    conn->file = fopen(filename, "w");
  } else {
    conn->file = fopen(filename, "r+");

    if (conn->file) {
      Database_load(conn);
    }
  }

  if (! conn->file) die("The shits with the file opening");

  return conn;
}

void Database_close(struct Connection *conn)
{
  if (conn) {
    if (conn->file) fclose(conn->file);
    if (conn->db) free(conn->db);
    free(conn);
  }
}

void Database_write(struct Connection *conn)
{
  rewind(conn->file);

  int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
  if (rc != 1) die("We cannot write to file: the shits.");

  rc = fflush(conn->file);

  if (rc == -1) die("OMG! No flushing this files.");
}

void Database_create(struct Connection *conn)
{
  int i = 0;

  for (i = 0; i < MAX_ROWS; i++) {
    struct Address addr = { .id = 1, .set = 0 };

    conn->db->rows[i] = addr;
  }
}

void Database_delete(struct Connection *conn, int id)
{
  struct Address addr = {.id = id, .set = 0};
  conn->db->rows[id] = addr;
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
  struct Address *addr = &conn->db->rows[id];
  if (addr->set) die("We are already set. Delete us first.");

  addr->set = 1;
  char *res = strncpy(addr->name, name, MAX_DATA);

  if (!res) die("Fuck yeah, copy failed for name");

  res = strncpy(addr->email, email, MAX_DATA);
  if (!res) die("Ouh yeah, copy failed for email");
}

void Database_get(struct Connection *conn, int id)
{
  struct Address *addr = &conn->db->rows[id];

  if (addr->set) {
    Address_print(addr);
  } else {
    die("Id is not set");
  }
}

void Database_list(struct Connection *conn)
{
  int i = 0;
  struct Database *db = conn->db;

  for (i = 0; i < MAX_ROWS; i++) {
    struct Address *addr = &db->rows[i];

    if (addr->set) {
      Address_print(addr);
    }
  }
}

int main(int argc, char *argv[])
{
  if(argc < 3) die("USAGE: ex17 <dbfile> <action> [action params]");

  char *filename = argv[1];
  char action = argv[2][0];
  struct Connection *conn = Database_open(filename, action);
  int id = 0;

  if(argc > 3) id = atoi(argv[3]);
  if(id >= MAX_ROWS) die("There's not that many records.");

  switch(action) {
    case 'c':
      Database_create(conn);
      Database_write(conn);
      break;

    case 'g':
      if(argc != 4) die("Need an id to get");

      Database_get(conn, id);
      break;

    case 's':
      if(argc != 6) die("Need id, name, email to set");

      Database_set(conn, id, argv[4], argv[5]);
      Database_write(conn);
      break;

    case 'd':
      if(argc != 4) die("Need id to delete");

      Database_delete(conn, id);
      Database_write(conn);
      break;

    case 'l':
      Database_list(conn);
      break;
    default:
      die("Invalid action, only: c=create, g=get, s=set, d=del, l=list");
  }

  Database_close(conn);

  return 0;
}
