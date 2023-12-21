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
process ./base/flog.h ./all/cgen.h
process ./base/fnt.h ./all/cgen.h
process ./base/gtype.h ./all/cgen.h
process ./cont/slist.h ./all/cgen.h
process ./cont/tmap.h ./all/cgen.h
process ./cont/vector.h ./all/cgen.h

echo "#endif  // CGEN_H_" >> ./all/cgen.h
