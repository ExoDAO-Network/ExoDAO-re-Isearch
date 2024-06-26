/* Copyright (c) 2020-21 Project re-Isearch and its contributors: See CONTRIBUTORS.
It is made available and licensed under the Apache 2.0 license: see LICENSE */
#ifndef BUFFER_HXX
#define BUFFER_HXX 1

class BUFFER {
public:
  BUFFER();
  BUFFER(size_t bytes, size_t size=sizeof(char));
  ~BUFFER();

  void  SetPageSize(size_t size);

  void *Want(size_t bytes, size_t size=sizeof(char)); // like malloc
  void *Expand(size_t bytes, size_t size=sizeof(char)); // like realloc

  void          *Ptr() const    { return (void *)Buffer; }
  signed char   *c_str() const  { return (signed char *)Buffer; }
  unsigned char *c_ustr() const { return Buffer; }

  bool  Ok() const;
  bool  Free();
  bool  Free(const char *What);
  bool  Free(const char *Class, const char *What);

  size_t   Size() const              { return Buffer_size;             }
  operator const char *() const      { return (const char *)Buffer;    }
  operator signed char *() const     { return (signed char *)Buffer;   }
  operator unsigned char * () const  { return (unsigned char *)Buffer; }
  operator void *() const            { return (void *)Buffer;          }
  operator STRING() const            { return STRING(Buffer);          }

private:
  size_t          PageSize;
  size_t          Buffer_size;
  unsigned char  *Buffer;
};

/*
TODO:
  CHARBUFFER -- buffer for sizeof(char)
  GPBUFFER -- buffer for sizeof(GPTYPE)
*/


#endif
