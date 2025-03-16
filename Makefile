# نام فایل اجرایی
TARGET = packet_sniffer

# فایل‌های سورس
SRCS = packet_sniffer.c

# کتابخانه‌های مورد نیاز
LIBS = -lpcap

CC = gcc
CFLAGS = -Wall -Wextra -O2


$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LIBS)


run: $(TARGET)
	sudo ./$(TARGET)

clean:
	rm -f $(TARGET) captured.pcap


help:
	@echo "Usage:"
	@echo "  make          - Compile the program"
	@echo "  make run      - Run the program with sudo"
	@echo "  make clean    - Remove compiled files and logs"
