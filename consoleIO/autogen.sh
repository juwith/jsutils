#! /bin/bash

rm -rf autom4te.cache
rm -f aclocal.m4 ltmain.sh

echo "Running aclocal..."
aclocal

echo "Running autoheader..."
autoheader

#echo "Running libtoolize..."
#libtoolize

echo "Running autoconf..."
autoconf

echo "Running automake..."
automake --foreign --add-missing

echo -e "\n\nCreate configure !!"
