TARGET = Sudoku.exe
BUILDFOLDER = build
CC =x86_64-w64-mingw32-g++

# WINAPILIBS = -lcomctl32 -lgdi32 -lgdiplus
# WINAPIRELATED = -municode -mwindows
# AVOIDMINGWDYNAMIC =
CFLAGS = -std=c++17 \
         -O0 -D_FORTIFY_SOURCE=2 -fstack-protector 
#-Wall -Wextra -Werror -Wshadow 
LDFLAGS = -fstack-protector -Wl,-O1,-pie,--dynamicbase,--nxcompat,--sort-common,--as-needed \
		-Wl,--image-base,0x140000000 -Wl,--disable-auto-image-base -mconsole
# $(AVOIDMINGWDYNAMIC) $(WINAPILIBS) $(WINAPIRELATED)
MMAIN = main.cpp Global.hpp
MSUDOKUAPP = SudokuApp.cpp SudokuApp.hpp
MLOGIC= Logic.cpp Logic.hpp 
MGUI = Gui.cpp Gui.hpp

MODULES = $(MMAIN) $(MSUDOKUAPP) $(MLOGIC) $(MGUI)

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