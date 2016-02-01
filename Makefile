#Make file

## Directories
BIN_FOLDER = bin
OBJ_FOLDER = obj
INC_FOLDER = inc
SRC_FOLDER = src
LIB_FOLDER = lib

#Common Files
COMMON_SRC_FOLDER = $(SRC_FOLDER)/Common
#COMMON_OBJ_FOLDER = $(OBJ_FOLDER)/Common

COMMON_SRC_FILES = $(COMMON_SRC_FOLDER)/Logger/Logging.cpp \
	           $(COMMON_SRC_FOLDER)/Sockets/ConnectionSocket.cpp \
		   $(COMMON_SRC_FOLDER)/Sockets/ListeningSocket.cpp
COMMON_OBJ_FILES = $(patsubst %.cpp,%.o,$(COMMON_SRC_FILES))
COMMON_DEP_FILES = $(patsubst %.o,%.d,$(COMMON_OBJ_FILES))


#Manager directories
MANAGER_SRC_FOLDER = $(SRC_FOLDER)/Manager
#MANAGER_OBJ_FOLDER = $(OBJ_FOLDER)/Manager
MANAGER_SRC_FILES = $(MANAGER_SRC_FOLDER)/main.cpp
MANAGER_OBJ_FILES = $(patsubst %.cpp,%.o,$(MANAGER_SRC_FILES))
MANAGER_DEP_FILES = $(patsubst %.o,%.d,$(MANAGER_OBJ_FILES))

#Agent directories
AGENT_SRC_FOLDER = $(SRC_FOLDER)/Agent
#AGENT_OBJ_FOLDER = $(OBJ_FOLDER)/Agent
AGENT_SRC_FILES = $(AGENT_SRC_FOLDER)/main.cpp
AGENT_OBJ_FILES = $(patsubst %.cpp,%.o,$(AGENT_SRC_FILES))
AGENT_DEP_FILES = $(patsubst %.o,%.d,$(AGENT_OBJ_FILES))

agent: common
	@echo $(COMMON_SRC_FILES)
	@echo $(COMMON_OBJ_FILES)
	@echo $(COMMON_DEP_FILES)
	@echo $(MANAGER_SRC_FILES)
	@echo $(MANAGER_OBJ_FILES)
	@echo $(MANAGER_DEP_FILES)
	@echo $(AGENT_SRC_FILES)
	@echo $(AGENT_OBJ_FILES)
	@echo $(AGENT_DEP_FILES)

common: $(COMMON_OBJ_FILES)
	

# Pull in dependency info for our objects
-include $(COMMON_DEP_FILES)
#-include $(MANAGER_DEP_FILES)
#-include $(AGENT_DEP_FILES)

#Rules for makeing .o files ------------

# Compile and generate dependency info
# 1. Compile the .cpp file
# 2. Generate dependency information, explicitly specifying the target name
# 3. The final three lines do a little bit of sed magic. The following
#    sub-items all correspond to the single sed command below:
#    a. sed: Strip the target (everything before the colon)
#    b. sed: Remove any continuation backslashes
#    c. fmt -1: List words one per line
#    d. sed: Strip leading spaces
#    e. sed: Add trailing colons
$(OBJ_FOLDER)/%.o : $(SRC_FOLDER)/%.cpp
	@echo "MAKING: " $@
	@echo "MAKING: " $<
	$(CXX) $(DEFINES) $(CFLAGS) -I $(INC_FOLDER) -o $@ -c $<
	$(CXX) -MM -MT $(OBJ_FOLDER)/$*.o $(DEFINES) $(CFLAGS) -I $(INC_FOLDER) \
		$(SRC_FOLDER)/$*.cpp > $(OBJ_FOLDER)/$*.d
	@cp -f $(OBJ_FOLDER)/$*.d $(OBJ_FOLDER)/$*.d.tmp
	@sed -e 's/.*://' -e 's/\\$$//' < $(OBJ_FOLDER)/$*.d.tmp | fmt -1 | \
		sed -e 's/^ *//' -e 's/$$/:/' >> $(OBJ_FOLDER)/$*.d
	@rm -f $(OBJ_FOLDER)/$*.d.tmp
#---------------------------------------

