# Cross-Platform System Resource Monitor

This is a simple C project that I made to learn how to track system performance like CPU and memory usage. It works on both Windows and Linux by checking what system it's running on.

## 📌 Why I Made This

I wanted to keep an eye on how my computer was performing while using things like games or 3D software. It was also a good chance to practice writing code that works on different operating systems.

## ✅ What It Does

- Shows how much memory is being used
- Shows estimated CPU usage (with a short delay for accuracy)
- Works on Windows and Linux
- Very light and fast

## ▶️ How to Run

### On Windows (using GCC or Visual Studio)
```bash
gcc monitor.c -o monitor.exe
monitor.exe
```

### On Linux
```bash
gcc monitor.c -o monitor
./monitor
```

## 🧠 What I Learned

- How to use C to read system info
- Differences between Windows and Linux system APIs
- Using conditional code with `#ifdef`
- Simple performance monitoring

## 📄 License

MIT License — you can use or improve it freely!
