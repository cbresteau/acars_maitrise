/* -*- c++ -*- */

#define ACARS_SEND_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "Acars_send_swig_doc.i"

%{
#include "Acars_send/acars_gen.h"
%}


%include "Acars_send/acars_gen.h"
GR_SWIG_BLOCK_MAGIC2(Acars_send, acars_gen);
