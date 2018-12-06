SRC=main3G.C image.C sink.C source.C PNMreader.C PNMwriter.C filter.C logging.C
OBJ=$(SRC:.C=.o)

prog: $(OBJ)
	g++ -std=c++11 $(OBJ) -o proj3C

.C.o: $<
	g++ -std=c++11 -g -I. -c $<

clean:
	rm *.o proj3C
