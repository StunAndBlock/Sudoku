TARGET = Sudoku.exe
BUILDFOLDER = build
SOURCEFOLDER = src
CC =x86_64-w64-mingw32-g++

LIBSABWINAPIGUI = -lsan_winapi_gui -Lsrc/Gui/StunAndBlock/
# WINAPILIBS = -lcomctl32 -lgdi32 -lgdiplus -luser32
MINGWWINDOWS = -mwindows -municode
# AVOIDMINGWDYNAMIC =
CFLAGS = -std=c++17 \
         -O0 -D_FORTIFY_SOURCE=2 -fstack-protector 
#-Wall -Wextra -Werror -Wshadow 
LDFLAGS = -fstack-protector -Wl,-O1,-pie,--dynamicbase,--nxcompat,--sort-common,--as-needed \
		-Wl,--image-base,0x140000000 -Wl,--disable-auto-image-base -mconsole \
		$(MINGWWINDOWS) $(LIBSABWINAPIGUI)


MMAIN = $(SOURCEFOLDER)/main.cpp $(SOURCEFOLDER)/Global.hpp
MSUDOKUAPPDIR = $(SOURCEFOLDER)/App
MSUDOKUAPP = $(MSUDOKUAPPDIR)/SudokuApp.cpp $(MSUDOKUAPPDIR)/SudokuApp.hpp
MLOGICDIR = $(SOURCEFOLDER)/Logic
MLOGIC= $(MLOGICDIR)/Logic.cpp $(MLOGICDIR)/Logic.hpp
MGUIDIR = $(SOURCEFOLDER)/Gui
MGUI = $(MGUIDIR)/Gui.cpp $(MGUIDIR)/Gui.hpp
MMENU = $(MGUIDIR)/Menu.cpp $(MGUIDIR)/Menu.hpp
MGUIALL = $(MGUI) $(MMENU)

MODULES = $(MMAIN) $(MSUDOKUAPP) $(MLOGIC) $(MGUIALL)

CPP = $(filter %.cpp,$(MODULES))
HEADERS = $(filter %.hpp %.h,$(MODULES))
OBJECTS = $(patsubst %.cpp,%.o,$(CPP))


.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS) | $(BUILDFOLDER)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(BUILDFOLDER)/$(TARGET)  

$(OBJECTS): %.o: %.cpp $(HEADERS)
	$(CC) -c $< -o $@


clean:
	rm -f $(OBJECTS)
	rm -f $(BUILDFOLDER)/$(TARGET)

run: $(BUILDFOLDER)/$(TARGET)  
	clear
	$(BUILDFOLDER)/$(TARGET)