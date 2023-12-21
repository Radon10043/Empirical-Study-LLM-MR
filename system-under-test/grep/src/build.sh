# Download
wget https://ftp.gnu.org/gnu/grep/grep-3.11.tar.gz

# Decompress
tar -xzvf grep-3.11.tar.gz
rm -r grep-3.11.tar.gz

# Compile and build
cd grep-3.11
mkdir obj-temp && cd obj-temp
../configure --disable-shared --prefix=$PWD
make