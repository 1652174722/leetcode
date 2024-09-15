TARGET = leetcode

SRC_OBJECTS=src/com_tool.o \
	src/graph/graph_directed/graph_unweighted/graph_du_topological_sort.o \
	src/graph/graph_directed/graph_unweighted/graph_du_shortest_path.o \

TEST_OBJECTS=test/gtest.o \
	test/template_test.o \
	test/graph/graph_directed/graph_unweighted/graph_du_topological_sort_test.o \
	test/graph/graph_directed/graph_unweighted/graph_du_shortest_path_test.o \
	test/graph/graph_directed/graph_weighted/graph_dijkstr_test.o \
	test/tree/binary_tree/search_binary_tree_test.o \
	test/tree/binary_tree/balance_binary_tree/avl_tree_test.o \
	test/common_algorithm/difference_array_test.o \
	test/tree/binary_indexed_tree/binary_indexed_tree_test.o \
	test/tree/segment_tree/segment_tree_test.o
	

ALL_OBJECTS=${SRC_OBJECTS} ${TEST_OBJECTS}

# CFLAGS +=-fprofile-arcs  -ftest-coverage

DFLAGS=-Lgtest/lib -lgtest -lpthread

INCLUDES = -Isrc \
		   -Isrc/graph/graph_directed/graph_unweighted \
		   -Isrc/graph/graph_directed/graph_weighted \
		   -Isrc/common_algorithm \
		   -Isrc/tree/binary_tree \
		   -Isrc/tree/binary_tree/balance_binary_tree \
		   -Isrc/tree/binary_indexed_tree \
		   -Isrc/tree/segment_tree \
		   -Itest \
		   -Igtest/include		   

LIB_HEAD_FILES = $(wildcard src/*.h) \
				 $(wildcard common_algorithm/*.h) \
				 $(wildcard graph/*.h) \
				 $(wildcard tree/*.h)


# -fsanitize=address -lasan
$(TARGET) : $(ALL_OBJECTS)
	g++ $(ALL_OBJECTS) -o $(TARGET) -g -Wall -std=c++11 $(CFLAGS) $(DFLAGS)
# g++ $(OBJECTS) -o $(TARGET) -g -Wall -std=c++11 -fstack-protector-all 
	@echo "build $(TARGET) successfully."

$(ALL_OBJECTS) : %.o : %.cpp
	g++ -g -Wall -std=c++11 $(CFLAGS) -c $< -o $@ $(INCLUDES)

.PHONY: clean
clean:
	@rm -rf $(TARGET) $(ALL_OBJECTS) test/*.gcda src/*.gcda  test/*.gcno src/*.gcno 

run : $(TARGET)
	./leetcode
