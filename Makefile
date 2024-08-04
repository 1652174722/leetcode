TARGET = leetcode

OBJECTS=src/com_tool.o \
	src/graph/topological_sort.o \
	test/gtest.o \
	test/leetcode_test.o \
	test/template_test.o \
	test/graph/topological_sort_test.o \
	test/tree/binary_tree/search_binary_tree_test.o \
	test/common_algorithm/difference_array_test.o \
	test/tree/binary_indexed_tree/binary_indexed_tree_test.o \
	test/tree/segment_tree/segment_tree_test.o 

# CFLAGS +=-fprofile-arcs  -ftest-coverage

DFLAGS=-Lgtest/lib -lgtest -lpthread

INCLUDES = -Isrc \
		   -Isrc/graph \
		   -Isrc/common_algorithm \
		   -Isrc/tree/binary_tree \
		   -Isrc/tree/binary_indexed_tree \
		   -Isrc/tree/segment_tree \
		   -Itest \
		   -Igtest/include		   

LIB_HEAD_FILES = $(wildcard src/*.h) \
				 $(wildcard common_algorithm/*.h) \
				 $(wildcard graph/*.h) \
				 $(wildcard tree/*.h)


# -fsanitize=address -lasan
$(TARGET) : $(OBJECTS)
	g++ $(OBJECTS) -o $(TARGET) -g -Wall -std=c++11 $(CFLAGS) $(DFLAGS)
# g++ $(OBJECTS) -o $(TARGET) -g -Wall -std=c++11 -fstack-protector-all 
	@echo "build $(TARGET) successfully."

$(OBJECTS) : %.o : %.cpp
	g++ -g -Wall -std=c++11 $(CFLAGS) -c $< -o $@ $(INCLUDES)

.PHONY: clean
clean:
	@rm -rf $(TARGET) $(OBJECTS) test/*.gcda src/*.gcda  test/*.gcno src/*.gcno 

run : $(TARGET)
	./leetcode
