IMPORTANT:for 7th argument: if 0 prints normally, 1 prints paging steps, 2 prints with random number

Code is commented properly
	-main.cpp
		-Random (.h,.cpp)
		-Frametable (.h)
		-FrameTableFIFO (.h,.cpp)
		-FrameTableLRU (.h,.cpp)
		-FrameTableRANDOM (.h,.cpp)
		-Process (.h,.cpp)
		-Pager (.h,.cpp)
	-Outputs for all inputs
	-.o files are executable files

To run the code: Change the output.txt file name accordingly or print into terminal

module load gcc-6.2.0
g++ -std=c++11 -c main.cpp FrametableFIFO.cpp FrametableLRU.cpp Random.cpp Pager.cpp Process.cpp FrametableRANDOM.cpp
g++ main.o FrametableFIFO.o Random.o Pager.o Process.o FrametableLRU.o FrametableRANDOM.o
./a.out 10 10 20 1 10 lru 0 > output1.txt