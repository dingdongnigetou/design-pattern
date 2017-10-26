
#!/bin/bash

currtent_path=`pwd`

wget https://github.com/google/googletest/archive/release-1.8.0.tar.gz
tar -xzv -f release-1.8.0.tar.gz
cd googletest-release-1.8.0
cd googletest/make/
make
ar rcs libgtest.a gtest-all.o
cp libgtest.a /usr/local/lib/

cd $currtent_path

