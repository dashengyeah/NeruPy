CPP_FLAGS = -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_core -L /home/dash/devtools/opencv/lib -I /home/dash/devtools/opencv/include

ImgPrep : imgpreprosesser.o
	g++ imgpreprosesser.o -o ImgPrep $(CPP_FLAGS)

imgpreprosesser.o : imgpreprosesser.cpp
	g++ -c imgpreprosesser.cpp -o imgpreprosesser.o

clean:
	rm -rf *.o
