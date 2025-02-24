#include <iostream>

void parse_args(int argc, char *argv[]) {
  for (int i = 0; i < argc; ++i)
    std::cout << "argv[" << i << "] = " << argv[i] << '\n';
}

auto main(int argc, char *argv[]) -> int {
  std::cout << "TESTING...\n";

  parse_args(argc, argv);

  return 0;
}
