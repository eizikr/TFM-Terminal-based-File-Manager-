# C-File-Explorer
My own file manager built with C and the `ncurses` library.
Provides a comprehensive set of command-line tools for navigating and managing files on Unix-like operating systems.

## 📖 Description
I built **Terminal User Interface (TUI)** from scratch as a self exercise. 
It leverages the `ncurses` library to create an interactive command-line application that allows users to perform common file management tasks without relying on a graphical desktop environment.
The application is designed to be lightweight, fast, and highly responsive, making it an ideal tool for server environments or low-resource systems.

## 🚀 Features
**Intuitive Navigation:** Navigate directories and files effortlessly using the up/down arrow keys and `Enter`.

**Hidden Files:** Toggle the visibility of hidden files and folders by launching the program with the `-a` flag.

**View:** Press `F2` to open and view the contents of any text file.

**Rename:** Press `c` to change the name of a selected file or directory.

**Create:** Press `F7` to create a new directory in the current path.

**Delete:** Press `F8` to safely delete a file or an empty directory after a confirmation prompt.

**Robust Error Handling:** The application handles common errors gracefully, providing clear feedback to the user and preventing crashes.

**Dynamic Display:** The UI automatically updates to reflect changes in the file system, ensuring you always have an up-to-date view of your current location.

## ⚙️ How to Use
**Prerequisites**
To compile and run this program, you will need the `ncurses` development library.

**On Debian/Ubuntu:**
```
sudo apt-get install libncurses-dev
```
**On Fedora/CentOS:**
```
sudo yum install ncurses-devel
```
**Compilation**
Use the provided `Makefile` to compile the project. The `Makefile` handles all dependencies and simplifies the build process.
```
make
```
**Running the Application**
Once compiled, you can run the executable from your terminal.

* **Standard launch:**
```
./file_explorer
```
* **Launch with hidden files:**
```
./file_explorer -a
```
# 🤝 Contributing
We welcome contributions from the community! To contribute to this project, please follow these steps:

1. Fork the repository.

2. Create a new branch for your feature or bug fix (`git checkout -b feature-name`).

3. Commit your changes (`git commit -m 'Add a new feature`).

4. Push to your branch (`git push origin feature-name`).

5. Open a Pull Request on the main repository.

## 📜 License
This project is licensed under the MIT License. See the `LICENSE` file for more details.

## ✉️ Contact
For any questions or support, please feel free to open an issue in this repository.
