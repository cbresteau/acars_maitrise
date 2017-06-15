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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "acars_gen_impl.h"

namespace gr {
  namespace Acars_send {

    acars_gen::sptr
    acars_gen::make(char* file)
    {
      return gnuradio::get_initial_sptr
        (new acars_gen_impl(file));
    }

    /*
     * The private constructor
     */
    acars_gen_impl::acars_gen_impl(char* file)
      : gr::sync_block("acars_gen",
      gr::io_signature::make(0, 0, 0),
        gr::io_signature::make(1, 1, sizeof(char))),
        preamble_sync{0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x2B,0x2A,0x16,0x16}
        /*preamble_sync_bit{11111111,11111111,11111111,11111111,11111111,11111111,11111111,11111111,11111111,11111111,11111111,
      11111111,11111111,11111111,11111111,11111111,00101011,00101010,00010110,00010110}*/
{


  myfile.open(file);
  int ret = myfile.is_open();
  printf("Fichier ouvert %d\n",ret);
}
    /*
     * Our virtual destructor.
     */
    acars_gen_impl::~acars_gen_impl()
    {
      myfile.close();
      printf("Fichier fermé\n");
    }


    /* -------------
     *  W O R K
     -------------*/

    int
    acars_gen_impl::work (int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      printf("Debut WORK\n");
      static int sent = 0;
      printf("%d\n",noutput_items);
      char *out = (char *) output_items[0];

      for(int i =0; i < noutput_items; i++){
      out[i] = 0;
      }

    consume_each (noutput_items);
    sent += noutput_items;
    //Compte du nombre de charactères du fichier

    char current_char;
    int c = 0;
    if (myfile.is_open()){

      printf("Fichier BIEN ouvert\n");
      while(myfile.get(current_char)){
        //printf("%c\n",current_char);
        if(current_char == EOF)
          {
            break;
          }
          c++;

          }
          printf("Taille : %d\n",c);
        }

    myfile.clear();
    myfile.seekg(0, std::ios::beg);

    unsigned char message[c-2]={0}; //Ca marche c-2 ??

    std::string line;
    getline (myfile,line);
    std::cout<<line;
    if (line.find("0x")==0) {
      printf("Trouvé!\n");

    int i = 0;

    for ( std::string::iterator it=(line.begin()+2); it!=line.end(); ++it){
        unsigned char hex = *it;
        unsigned char conv;

  printf("Conversion en cours %c\n",c);
        switch(toupper(hex))
    {

        case '0': conv = 0;
        break;
        case '1': conv = 1;
        break;
        case '2': conv = 2;
        break;
        case '3': conv = 3;
        break;
        case '4': conv = 4;
        break;
        case '5': conv = 5;
        break;
        case '6': conv = 6;
        break;
        case '7': conv = 7;
        break;
        case '8': conv = 8;
        break;
        case '9': conv = 9;
        break;
        case 'A': conv = 10;
        break;
        case 'B': conv = 11;
        break;
        case 'C': conv = 12;
        break;
        case 'D': conv = 13;
        break;
        case 'E': conv = 14;
        break;
        case 'F': conv = 15;
        break;
    }


    message[i/2]= message[i/2] | (conv<< (4*(1-i%2)));
    ++i;

    }
  }

  for(int i=0 ; i < c ; i ++ ){
        std::cout << message[i];
  }

  memcpy(out,preamble_sync,20*sizeof(char));
  memcpy(out+20,message,c*sizeof(char));
  return noutput_items;
  return -1;

    }

  } /* namespace Acars_send */
} /* namespace gr */
