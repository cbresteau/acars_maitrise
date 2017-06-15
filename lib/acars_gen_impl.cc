/* -*- c++ -*- */
/*
 * Copyright 2012 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/thread/thread.h>
#include "acars_gen_impl.h"
#include <gnuradio/io_signature.h>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdexcept>
#include <stdio.h>

// win32 (mingw/msvc) specific
#ifdef HAVE_IO_H
#include <io.h>
#endif
#ifdef O_BINARY
#define	OUR_O_BINARY O_BINARY
#else
#define	OUR_O_BINARY 0
#endif
// should be handled via configure
#ifdef O_LARGEFILE
#define	OUR_O_LARGEFILE	O_LARGEFILE
#else
#define	OUR_O_LARGEFILE 0
#endif

namespace gr {
  namespace Acars_send {

    acars_gen::sptr acars_gen::make(char *filename)
    {
      return gnuradio::get_initial_sptr
	(new acars_gen_impl(filename));
    }

    acars_gen_impl::acars_gen_impl(char *filename)
      : sync_block("acars_gen",
		      io_signature::make(0, 0, 0),
		      io_signature::make(1, 1, 1)),
	d_itemsize(1), d_fp(0), d_new_fp(0), d_repeat(0),
	d_updated(false)
    {
      open(filename, d_repeat);
      do_update();
    }

    acars_gen_impl::~acars_gen_impl()
    {
      if(d_fp)
        fclose ((FILE*)d_fp);
      if(d_new_fp)
        fclose ((FILE*)d_new_fp);
    }

    bool
    acars_gen_impl::seek(long seek_point, int whence)
    {
      return fseek((FILE*)d_fp, seek_point *d_itemsize, whence) == 0;
    }


    void
    acars_gen_impl::open(const char *filename, bool repeat)
    {
      // obtain exclusive access for duration of this function
      gr::thread::scoped_lock lock(fp_mutex);

      int fd;

      // we use "open" to use to the O_LARGEFILE flag
      if((fd = ::open(filename, O_RDONLY | OUR_O_LARGEFILE | OUR_O_BINARY)) < 0) {
	perror(filename);
	throw std::runtime_error("can't open file");
      }

      if(d_new_fp) {
	fclose(d_new_fp);
	d_new_fp = 0;
      }

      if((d_new_fp = fdopen (fd, "rb")) == NULL) {
	perror(filename);
	::close(fd);	// don't leak file descriptor if fdopen fails
	throw std::runtime_error("can't open file");
      }

      d_updated = true;
      d_repeat = repeat;
    }

    void
    acars_gen_impl::close()
    {
      // obtain exclusive access for duration of this function
      gr::thread::scoped_lock lock(fp_mutex);

      if(d_new_fp != NULL) {
	fclose(d_new_fp);
	d_new_fp = NULL;
      }
      d_updated = true;
    }

    void
    acars_gen_impl::do_update()
    {
      if(d_updated) {
	gr::thread::scoped_lock lock(fp_mutex); // hold while in scope

	if(d_fp)
	  fclose(d_fp);

	d_fp = d_new_fp;    // install new file pointer
	d_new_fp = 0;
	d_updated = false;
      }
    }

    int
    acars_gen_impl::work(int noutput_items,
			   gr_vector_const_void_star &input_items,
			   gr_vector_void_star &output_items)
    {
      char *o = (char*)output_items[0];
      int i;
      int size = noutput_items;

      char hex;


      do_update();       // update d_fp is reqd
      if(d_fp == NULL)
	throw std::runtime_error("work with file not open");

      gr::thread::scoped_lock lock(fp_mutex); // hold for the rest of this function

      while(size) {

	i = fread(&hex, d_itemsize, 1, (FILE*)d_fp);

        switch(toupper(hex))
    {

        case '0': *o = 0<<4;
        break;
        case '1': *o = 1<<4;
        break;
        case '2': *o = 2<<4;
        break;
        case '3': *o = 3<<4;
        break;
        case '4': *o = 4<<4;
        break;
        case '5': *o = 5<<4;
        break;
        case '6': *o = 6<<4;
        break;
        case '7': *o = 7<<4;
        break;
        case '8': *o = 8<<4;
        break;
        case '9': *o = 9<<4;
        break;
        case 'A': *o = 10<<4;
        break;
        case 'B': *o = 11<<4;
        break;
        case 'C': *o = 12<<4;
        break;
        case 'D': *o = 13<<4;
        break;
        case 'E': *o = 14<<4;
        break;
        case 'F': *o = 15<<4;
        break;
    }

    i = fread(&hex, d_itemsize, 1, (FILE*)d_fp);

          switch(toupper(hex))
      {

          case '0': *o |= 0;
          break;
          case '1': *o |= 1;
          break;
          case '2': *o |= 2;
          break;
          case '3': *o |= 3;
          break;
          case '4': *o |= 4;
          break;
          case '5': *o |= 5;
          break;
          case '6': *o |= 6;
          break;
          case '7': *o |= 7;
          break;
          case '8': *o |= 8;
          break;
          case '9': *o |= 9;
          break;
          case 'A': *o |= 10;
          break;
          case 'B': *o |= 11;
          break;
          case 'C': *o |= 12;
          break;
          case 'D': *o |= 13;
          break;
          case 'E': *o |= 14;
          break;
          case 'F': *o |= 15;
          break;
      }

	size -= i;
	o += i * d_itemsize;

	if(size == 0)		// done
	  break;

	if(i > 0)			// short read, try again
	  continue;

	// We got a zero from fread.  This is either EOF or error.  In
	// any event, if we're in repeat mode, seek back to the beginning
	// of the file and try again, else break
	if(!d_repeat)
	  break;

	if(fseek ((FILE *) d_fp, 0, SEEK_SET) == -1) {
	  fprintf(stderr, "[%s] fseek failed\n", __FILE__);
	  exit(-1);
	}
      }
printf("j'ai finis %d; %d\n", size, noutput_items);
      if(size > 0) {	     		// EOF or error
	if(size == noutput_items)       // we didn't read anything; say we're done
	  return -1;
	return noutput_items - size;	// else return partial result
      }

      return noutput_items;
    }

  } /* namespace blocks */
} /* namespace gr */
