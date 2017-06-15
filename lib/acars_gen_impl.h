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

#ifndef INCLUDED_ACARS_SEND_ACARS_GEN_IMPL_H
#define INCLUDED_ACARS_SEND_ACARS_GEN_IMPL_H

#include <Acars_send/acars_gen.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string.h>

namespace gr {
  namespace Acars_send {

    class acars_gen_impl : public acars_gen
    {
     private:
       std::ifstream myfile;
       float preamble_sync[20];

     public:
      acars_gen_impl(char* file);
      ~acars_gen_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace Acars_send
} // namespace gr

#endif /* INCLUDED_ACARS_SEND_ACARS_GEN_IMPL_H */
