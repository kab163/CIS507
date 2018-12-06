SRC=main3C.C image.C sink.C source.C PNMreader.C PNMwriter.C filter.C
OBJ=$(SRC:.C=.o)

prog: $(OBJ)
	g++ -std=c++11 $(OBJ) -o proj3C

.C.o: $<
	g++ -std=c++11 -I. -c $<

clean:
	rm *.o proj3C
