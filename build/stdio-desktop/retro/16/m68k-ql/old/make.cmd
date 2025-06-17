
rem docker run -it -v D:/_test:/_test -w /_test -u root xora/qdos-devel bash

docker run -v D:/_test:/_test -w /_test -u root xora/qdos-devel qdos-gcc -o hello hello.c

pause

