#include "int_sorter.h"

int main(){
  const char input_filename[] = "toydata.txt";
  const char output_filename[] = "result.txt";
  IntSorterError result = int_sorter(input_filename, output_filename);
  return 0;
}

