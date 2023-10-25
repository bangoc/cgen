#!/bin/bash
echo "/** (C) Nguyễn Bá Ngọc 2023" > ./all/cgen.h
echo -n " *  cgen version:" >> ./all/cgen.h
cat ./VERSION >> ./all/cgen.h
echo -e "\n */" >> ./all/cgen.h
echo "#ifndef CGEN_H_" >> ./all/cgen.h
echo "#define CGEN_H_" >> ./all/cgen.h

process() {
  echo -e "\n/***** $1 *****/" >> $2
  gcc -fpreprocessed -dD -P -E $1 | sed "/#include \"/d" >> $2
}
process ./base/gtype.h ./all/cgen.h
process ./base/flog.h ./all/cgen.h
process ./cont/vector.h ./all/cgen.h
process ./cont/queue.h ./all/cgen.h
process ./cont/slist.h ./all/cgen.h
process ./cont/dlist.h ./all/cgen.h
process ./cont/tmap.h  ./all/cgen.h
process ./algo/perm.h ./all/cgen.h
process ./utils/bench.h ./all/cgen.h

echo "#endif  // CGEN_H_" >> ./all/cgen.h

echo "/** (C) Nguyễn Bá Ngọc 2023" > ./all/cgen.c
echo -n " *  cgen version:" >> ./all/cgen.c
cat ./VERSION >> ./all/cgen.c
echo -e "\n */" >> ./all/cgen.c

echo '#include "cgen.h"' >> ./all/cgen.c
process ./cont/vector.c ./all/cgen.c
process ./cont/queue.c ./all/cgen.c
process ./cont/slist.c ./all/cgen.c
process ./cont/dlist.c ./all/cgen.c
process ./cont/tmap.c ./all/cgen.c
process ./algo/perm.c ./all/cgen.c