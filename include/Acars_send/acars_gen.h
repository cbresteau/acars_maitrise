/* -*- c++ -*- */
/* 
 * Copyright 2017 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */


#ifndef INCLUDED_ACARS_SEND_ACARS_GEN_H
#define INCLUDED_ACARS_SEND_ACARS_GEN_H

#include <Acars_send/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace Acars_send {

    /*!
     * \brief <+description of block+>
     * \ingroup Acars_send
     *
     */
    class ACARS_SEND_API acars_gen : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<acars_gen> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of Acars_send::acars_gen.
       *
       * To avoid accidental use of raw pointers, Acars_send::acars_gen's
       * constructor is in a private implementation
       * class. Acars_send::acars_gen::make is the public interface for
       * creating new instances.
       */
      static sptr make(char* file);
    };

  } // namespace Acars_send
} // namespace gr

#endif /* INCLUDED_ACARS_SEND_ACARS_GEN_H */

