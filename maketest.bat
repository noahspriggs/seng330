g++ src/*.cpp googletest/src/gtest-all.cc tests/*.cpp -D_WIN32_WINNT=0x0501 -DRISKTEST -DSFML_STATIC -static -static-libgcc -static-libstdc++ -o bin/risk -Isrc -Iinclude -Igoogletest/include -Igoogletest -Llib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio