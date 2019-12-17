CC = gcc 
CFLAGS = -g -Wall 
EXE = Main

all : $(EXE)

.PHONY : clean
clean :
	rm -f *.o core $(EXE)

%.o: %.c *.h 
	$(CC) $(CFLAGS) -c $<

$(EXE): % : %.o readData.o globalAl.o localAl.o stack.o
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depends on $^"
	@echo "# $< has Changed"
	$(CC) $(CFLAGS) -o $@ $@.o readData.o globalAl.o localAl.o stack.o
	
GlobalAlign_test:
	@echo Executing Main for Global Alignment on test data files
	@./Main global data/affine1d.fasta data/affine1q.fasta data/affine2d.fasta data/affine2q.fasta
	
LocalAlign_test:
	@echo Executing Main for Local Alignment on test data files
	@./Main local data/local1d.fasta data/local1q.fasta data/local2d.fasta data/local2q.fasta data/local3d.fasta data/local3q.fasta data/local5d.fasta data/local5q.fasta
