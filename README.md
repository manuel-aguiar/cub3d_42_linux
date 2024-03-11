cub3D Invalid Maps Tester

Test your 42 School cub3D's parsing against a list of invalid maps


Prerequisites:

- Your executable is named cub3D, as requested per the project's subject
- If you use the valgrind option, make sure your executable is compiled without -fsanitize statements


Instructions:

- Place the contents of this repository next to your cub3D executable
- Run: chmod 777 ./tester.sh; ./tester.sh [valgrind]


Evaluating the results:

- Your program must not open a window during the whole execution of the ./tester.sh command listed above
  If it does, it is opening an invalid map, which can result in erroneous behaviour later on.
- You can use the valgrind rule to check for leaks during execution of the ./tester.sh command listed above
  Compilation of -fsanitize statements without this rule can further help in this regard
- At the time of writing, this program has not been tested against final cub3D projects.
  Please, see this program as an auxiliar program and not as a means of final testing.

Thank you!
