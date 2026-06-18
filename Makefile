# 體育器材租借系統 - Makefile

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
INCLUDE = -I.

SRCDIR = .
OBJDIR = obj
BINDIR = .

SOURCES = $(wildcard *.cpp)
OBJECTS = $(patsubst %.cpp, $(OBJDIR)/%.o, $(SOURCES))
TARGET = $(BINDIR)/rental_system

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "編譯完成！可執行文件: $(TARGET)"

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(TARGET)
	@echo "清理完成！"

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
