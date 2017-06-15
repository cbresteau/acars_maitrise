#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/corentin/gnu_radio/gr-Acars_send/python
export PATH=/home/corentin/gnu_radio/gr-Acars_send/build/python:$PATH
export LD_LIBRARY_PATH=/home/corentin/gnu_radio/gr-Acars_send/build/lib:$LD_LIBRARY_PATH
export PYTHONPATH=/home/corentin/gnu_radio/gr-Acars_send/build/swig:$PYTHONPATH
/usr/bin/python2 /home/corentin/gnu_radio/gr-Acars_send/python/qa_acars_gen.py 
