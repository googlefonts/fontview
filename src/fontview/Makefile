fontview: *.cpp
	g++ -std=c++11 *.cpp `pkg-config --cflags --libs fribidi harfbuzz freetype2 raqm` `wx-config --cflags --libs` -I .. -o fontview

clean:
	rm -f fontview
