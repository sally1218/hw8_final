# 體育器材租借系統 - Makefile

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
INCLUDE = -Iinclude

SRCDIR = src
OBJDIR = obj
BINDIR = .

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))
TARGET = $(BINDIR)/rental_system

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "編譯完成！可執行文件: $(TARGET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(TARGET)
	@echo "清理完成！"

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
