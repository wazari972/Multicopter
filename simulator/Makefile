ARDU_INC = -I. -I/usr/share/arduino/hardware/arduino/variants/kk2/
DFLAGS = -g -O0
CXXFLAGS = $(DFLAGS) $(ARDU_INC) -fpermissive
CXX = g++

OBJECTS = KK2LCD.o project.o conv.o ardu.o WString.o

QTFLAGS = -pipe -march=x86-64 -mtune=generic  -pipe -fstack-protector --param=ssp-buffer-size=4  -W -D_REENTRANT -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED $(DFLAGS)
QTINC = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 
QTLIBS = -lQtGui -lQtCore -lpthread 

KK2LCD.o : ./LCD/KK2LCD.c
	$(CXX) -c $(CXXFLAGS) -I../simulator/LCD $(<) -o $(@)


project.o : project.c
	$(CXX) -c $(CXXFLAGS) -I../simulator/LCD $(<) -o $(@)


WString.o : /usr/share/arduino/hardware/arduino/cores/arduino/WString.cpp
	$(CXX) -c $(CXXFLAGS) $(<) -o $(@)

conv.o : conv.c
	$(CXX) -c $(CXXFLAGS) $(<) -o $(@)

ardu.o : ardu.c
	$(CXX) -c $(CXXFLAGS)  $(<) -o $(@)

#############

main.o : main.c
	$(CXX) -c $(CXXFLAGS)  $(<) -o $(@)

main : $(OBJECTS) main.o
	$(CXX)  $(OBJECTS) main.o -o $(@)

############

DEFINES       = -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4  -I.
moc_emulino-gui.cpp: emulino-gui.h
	/usr/lib/qt4/bin/moc $(DEFINES) $(INCPATH) emulino-gui.h -o moc_emulino-gui.cpp

emulino-gui.moc : emulino-gui.cpp
	/usr/lib/qt4/bin/moc $(DEFINES) $(INCPATH) emulino-gui.cpp -o emulino-gui.moc

emulino-gui.o : emulino-gui.cpp moc_emulino-gui.cpp emulino-gui.moc
	$(CXX) -c $(QTFLAGS) $(QTINC) $(<) -o $(@) 

moc_emulino-gui.o: moc_emulino-gui.cpp
	$(CXX) -c $(QTFLAGS) $(INCPATH) -o moc_emulino-gui.o moc_emulino-gui.cpp

emulino-gui : emulino-gui.o moc_emulino-gui.o $(OBJECTS)
	$(CXX) -o emulino-gui $(QTLIBS) $(OBJECTS) emulino-gui.o  moc_emulino-gui.o 

project : $(OBJECTS)
	$(CXX) -o $(@) $(OBJECTS)

clean :
	rm -f project main emulino-gui *.o

mrclean : clean
	rm -f emulino-gui.moc moc_emulino-gui.cpp simulator.pro