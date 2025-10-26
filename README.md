# gatsby-driver
A kernel driver that exposes a file from which The Great Gatsby’s full text can be read in an infinite loop.

# Compiling

## Debian Bookworm

### Install Kernel Headers + Build Tools

```bash
sudo apt update
sudo apt install linux-headers-$(uname -r)
sudo apt install build-essential
```

### Making the module

```bash
make clean
make all
```

# Usage

Make sure you are in the same directory as the compiled module and run:

`sudo insmod gatsby.ko`

Then check logs to see what major number gatsby is using:

`sudo dmesg | tail`

You should see a line like this:

`[ 1010.494459] gatsby: Major number obtained (236)`

Make a device file at /dev/gatsby and replace '<major_number>' with the number reported:

`sudo mknod /dev/gatsby c <major_number> 0`

Now you should be able to scroll the text by using:

`less -f /dev/gatsby`
