all: lib/libStore.so lib/libToolChain.so lib/libMyTools.so include/Tool.h lib/libDataModel.so

	g++ src/main.cpp -o main -I include/ -L lib/ -lMyTools -lToolChain -lStore -lDataModel -I ../include/ -lpthread #-L/usr/lib64/root -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lMathCore -lThread -pthread -lm -ldl -rdynamic -pthread -m64 -I/usr/include/root -lusb -I ../include # ../obj/PSEC4_EVAL.o  ../obj/stdUSBl.o  ../obj/ScopePipe.o 

lib/libStore.so:

	g++ --shared -c -I src/Store/ src/Store/Store.cpp -o lib/libStore.so
	cp src/Store/Store.h include/

include/Tool.h:
	cp src/Tool/Tool.h include/

lib/libToolChain.so: lib/libStore.so include/Tool.h lib/libDataModel.so

	g++ -c --shared src/ToolChain/ToolChain.cpp -I src/ToolChain/ -I include -L /lib -lStore -o lib/libToolChain.so  -L/usr/lib64/root -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lMathCore -lThread -pthread -lm -ldl -rdynamic -lpthread -m64 -I/usr/include/root
	cp src/ToolChain/*.h include/ 

lib/libDataModel.so:  lib/libStore.so 
	g++ -c --shared DataModel/DataModel.cpp -I DataModel/ -o lib/libDataModel.so -L/usr/lib64/root -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lMathCore -lThread -pthread -lm -ldl -rdynamic -pthread -m64 -I/usr/include/root -I include -L /lib -lStore
	cp DataModel/*.h include/ 

clean: 

	rm lib/*
	rm include/*






lib/libMyTools.so: lib/libStore.so include/Tool.h lib/libDataModel.so

	g++  --shared -c UserTools/Unity.cpp -I UserTools/ -I include -L lib -lStore -lDataModel -o lib/libMyTools.so #../obj/PSEC4_EVAL.o  ../obj/stdUSBl.o  ../obj/ScopePipe.o -I ../include/ -L/usr/lib64/root -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lMathCore -lThread -pthread -lm -ldl -rdynamic -pthread -m64 -I/usr/include/root -lusb -I ../include
	cp UserTools/*.h include/
