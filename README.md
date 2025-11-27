## 🖥️ GTK3 Scientific Calculator Setup on Windows (MSYS2)

This guide shows how to set up a C GTK3 scientific calculator on Windows using **MSYS2**.

---

## 1️⃣ Open Terminal

Use the **MSYS2 MinGW 64-bit terminal**, **not** CMD or PowerShell.

---

## 2️⃣ Update MSYS2

```bash
pacman -Su           # Update core system packages
pacman -Syu          # Full system upgrade
# ⚠️ Close & reopen terminal if required
```

---

## 3️⃣ Install Required Packages

```bash
pacman -S mingw-w64-x86_64-gtk3        # GTK3 library
pacman -S mingw-w64-x86_64-toolchain  # GCC, g++, make, etc.
pacman -S mingw-w64-x86_64-pkg-config # pkg-config utility
```

---

## 4️⃣ Set PKG_CONFIG_PATH

```bash
export PKG_CONFIG_PATH=/mingw64/lib/pkgconfig
# 📝 Allows pkg-config to locate GTK3 headers & libraries
```

---

## 5️⃣ Navigate to Your Project Folder

```bash
cd "/c/Path/To/Your/Project"
ls   # Should show main.c, calc.c, calc.h
# ⚠️ Avoid spaces in filenames
```

---

## 6️⃣ Compile the Scientific Calculator

```bash
gcc main.c calc.c evaluation.c -o dist/calculator $(pkg-config --cflags --libs gtk+-3.0) -lm
# Explanation:
# - $(pkg-config --cflags --libs gtk+-3.0) → fetch GTK3 compiler & linker flags
# - -lm → link the math library
```

---

## 7️⃣ Run Your Calculator

```bash
calculator.exe
```

---

## 8️⃣ Tips & Adjustments

- Increase GTK button sizes: `gtk_widget_set_size_request(button, width, height)`
- Adjust grid spacing for clean layout:

  - `gtk_grid_set_row_spacing(grid, value)`
  - `gtk_grid_set_column_spacing(grid, value)`

- Keep MSYS2 & GTK3 up to date
- Always compile in **MSYS2 MinGW 64-bit terminal**

---

## 9️⃣ Troubleshooting

- `gcc: command not found` → Ensure `mingw-w64-x86_64-toolchain` installed
- `Package 'gtk+-3.0' not found` → Check GTK3 installation & `PKG_CONFIG_PATH`
- GUI layout broken → Adjust grid spacing for consistent gaps

```

This version:

- ✅ Uses **Markdown headings** for hierarchy
- ✅ Includes **step numbers**
- ✅ Shows **all commands inside bash code blocks**
- ✅ Contains **notes, tips, warnings, and emojis**
```
