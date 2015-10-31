mkdir -p obj

src="."
obj="$src/obj"

FLAGS_ANSI="\
    -Os \
    -std=c89 \
    -ansi \
    -pedantic \
    -Wall"
FLAGS_x86="\
    -Os \
    -masm=intel \
    -pedantic \
    -Wall"

C_FLAGS=$FLAGS_x86

echo Compiling C source code...
cc -o $obj/main.asm             $src/main.c     -S $C_FLAGS
cc -o $obj/input.asm            $src/input.c    -S $C_FLAGS
cc -o $obj/doors.asm            $src/doors.c    -S $C_FLAGS

echo Assembling compiled sources...
as -o $obj/main.o               $obj/main.asm
as -o $obj/input.o              $obj/input.asm
as -o $obj/doors.o              $obj/doors.asm

echo Linking assembled object files...
gcc -o $src/mh $obj/doors.o $obj/input.o $obj/main.o -s
